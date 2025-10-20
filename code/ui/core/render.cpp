#include "framebuffer.h"
extern "C" {
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
#include <iostream>
void renderVideo(VideoClip &clip, const std::string &outputFile) {
    AVFormatContext *outFmtCtx = nullptr;
    AVCodecContext *encCtx = nullptr;
    AVStream *outStream = nullptr;
    avformat_alloc_output_context2(&outFmtCtx, nullptr, nullptr, outputFile.c_str());
    if (!outFmtCtx) {
        std::cerr << "Failed to create output context\n";
        return;
    }

    const AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!codec) {
        std::cerr << "H264 encoder not found\n";
        return;
    }
    outStream = avformat_new_stream(outFmtCtx, codec);
    if (!outStream) {
        std::cerr << "Failed to create stream\n";
        return;
    }
    encCtx = avcodec_alloc_context3(codec);
    encCtx->width = clip.width;
    encCtx->height = clip.height;
    encCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    encCtx->time_base = {1, clip.frameRate};

    if (outFmtCtx->oformat->flags & AVFMT_GLOBALHEADER)
        encCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

    if (avcodec_open2(encCtx, codec, nullptr) < 0) {
        std::cerr << "Failed to open encoder\n";
        return;
    }

    avcodec_parameters_from_context(outStream->codecpar, encCtx);

    if (!(outFmtCtx->oformat->flags & AVFMT_NOFILE)) {
        if (avio_open(&outFmtCtx->pb, outputFile.c_str(), AVIO_FLAG_WRITE) < 0) {
            std::cerr << "Could not open output file\n";
            return;
        }
    }

    if (avformat_write_header(outFmtCtx, nullptr) < 0) {
        std::cerr << "Failed writing header\n";
        return;
    }

        SwsContext *swsCtx = sws_getContext(
        clip.width, clip.height, AV_PIX_FMT_BGR24,
        clip.width, clip.height, encCtx->pix_fmt,
        SWS_BILINEAR, nullptr, nullptr, nullptr
    );

    AVFrame *frame = av_frame_alloc();
    frame->format = encCtx->pix_fmt;
    frame->width = clip.width;
    frame->height = clip.height;
    av_frame_get_buffer(frame, 32);

    AVPacket *pkt = av_packet_alloc();

      for (int i = 0; i < clip.frames.size(); i++) {
        cv::Mat bgr = clip.frames[i];  
        const uint8_t *srcSlice[1] = { bgr.data };
        int srcStride[1] = { static_cast<int>(bgr.step) };

        sws_scale(swsCtx, srcSlice, srcStride, 0, clip.height,
                  frame->data, frame->linesize);
      frame->pts = i;
      if (avcodec_send_frame(encCtx, frame) < 0) {
            std::cerr << "Error sending frame " << i << "\n";
            continue;
        }
       while (avcodec_receive_packet(encCtx, pkt) == 0) {
            pkt->stream_index = outStream->index;
            av_interleaved_write_frame(outFmtCtx, pkt);
            av_packet_unref(pkt);
        }
    }
    avcodec_send_frame(encCtx, nullptr);
    while (avcodec_receive_packet(encCtx, pkt) == 0) {
        pkt->stream_index = outStream->index;
        av_interleaved_write_frame(outFmtCtx, pkt);
        av_packet_unref(pkt);
    }
    av_write_trailer(outFmtCtx);
    av_packet_free(&pkt);
    av_frame_free(&frame);
    sws_freeContext(swsCtx);
    avcodec_free_context(&encCtx);
    if (!(outFmtCtx->oformat->flags & AVFMT_NOFILE)) {
        avio_close(outFmtCtx->pb);
    }
    avformat_free_context(outFmtCtx);

    std::cout << "✅ Render finished: " << outputFile << "\n";
}

