#include "ijksdl_aout_qt.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavutil/time.h"
#include "ijksdl/ijksdl_inc_internal.h"
#include "ijksdl/ijksdl_thread.h"
#include "ijksdl/ijksdl_aout_internal.h"
#ifdef __cplusplus
}
#endif

#include <stdbool.h>
#include <assert.h>

#define SDL_QT_AUDIO_MAX_CALLBACKS_PER_SEC 20

struct SDL_Aout_Opaque {
    SDL_cond   *wakeup_cond;
    SDL_mutex  *wakeup_mutex;
    
    QThread *thread;
    SDL_AudioSpec spec;
    
#if defined(QT6)
    QAudioDevice *device;
    QMediaDevices *devices;
    QAudioSink *audio;
#else
    QAudioOutput *audio;
#endif
    
    QIODevice *io;
    uint8_t *buffer;
    size_t buffer_size;
    
    //provider
    AudioDataProvider *provider;
    
    
    volatile bool need_flush;
    volatile bool pause_on;
    volatile bool abort_request;

    SDL_Thread *audio_tid;
    SDL_Thread _audio_tid;
    
    volatile bool need_set_volume;
    volatile float left_volume;
    volatile float right_volume;
    
    volatile float speed;
    volatile bool speed_changed;
};

//class AudioHandler: public QObject {
//    Q_OBJECT
//public:
//    explicit AudioHandler();
//    ~AudioHandler();
//
//public slots:
//
//signals:
//
//private:
//};

static int aout_thread(void *arg)
{
    SDL_Aout *aout = (SDL_Aout *)arg;
    SDL_Aout_Opaque *opaque = aout->opaque;
    SDL_AudioCallback audio_cblk = opaque->spec.callback;
    void *userdata = opaque->spec.userdata;
    uint8_t *buffer = opaque->buffer;
    int copy_size = 0;

    assert(opaque->io);
    assert(buffer);
    
    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);

    if (!opaque->abort_request && !opaque->pause_on){
//        SDL_Android_AudioTrack_play(env, atrack);
    }


    while (!opaque->abort_request) {
        SDL_LockMutex(opaque->wakeup_mutex);
        if (!opaque->abort_request && opaque->pause_on) {
//            SDL_Android_AudioTrack_pause(env, atrack);
            while (!opaque->abort_request && opaque->pause_on) {
                SDL_CondWaitTimeout(opaque->wakeup_cond, opaque->wakeup_mutex, 1000);
            }
            if (!opaque->abort_request && !opaque->pause_on) {
                if (opaque->need_flush) {
                    opaque->need_flush = 0;
//                    SDL_Android_AudioTrack_flush(env, atrack);
                }
//                SDL_Android_AudioTrack_play(env, atrack);
            }
        }
        if (opaque->need_flush) {
            opaque->need_flush = 0;
//            SDL_Android_AudioTrack_flush(env, atrack);
        }
        if (opaque->need_set_volume) {
            opaque->need_set_volume = 0;
//            SDL_Android_AudioTrack_set_volume(env, atrack, opaque->left_volume, opaque->right_volume);
        }
        if (opaque->speed_changed) {
            opaque->speed_changed = 0;
//            SDL_Android_AudioTrack_setSpeed(env, atrack, opaque->speed);
        }
        SDL_UnlockMutex(opaque->wakeup_mutex);
        
//        if (audio->state() == QAudio::SuspendedState || audio->state() == QAudio::StoppedState) {
//            audio->resume();
//        } else if (audio->state() == QAudio::ActiveState) {
//            audio->suspend();
//        } else if (audio->state() == QAudio::IdleState) {
//            // no-op
//        }
        
        copy_size = (int)opaque->audio->bytesFree();
        printf("status = %d, copy size = %d \n", opaque->audio->state(), copy_size);
        audio_cblk(userdata, buffer, copy_size);
        if (opaque->need_flush) {
//            SDL_Android_AudioTrack_flush(env, atrack);
            opaque->need_flush = false;
        }

        if (opaque->need_flush) {
            opaque->need_flush = 0;
//            SDL_Android_AudioTrack_flush(env, atrack);
        } else {
//            int written = SDL_Android_AudioTrack_write(env, atrack, buffer, copy_size);
//            if (written != copy_size) {
//                ALOGW("AudioTrack: not all data copied %d/%d", (int)written, (int)copy_size);
//            }
            if(copy_size > 0) {
                opaque->io->write((const char *)buffer, (qint64)copy_size);
                
                static FILE *file = fopen("", "wb+");
                if(file) {
                    fwrite(buffer, 1, copy_size, file);
                }
            }
            av_usleep(20 * 1000);
        }

        // TODO: 1 if callback return -1 or 0
    }

//    SDL_Android_AudioTrack_free(env, atrack);
    return 0;
}


static int aout_open_audio(SDL_Aout *aout, const SDL_AudioSpec *desired, SDL_AudioSpec *obtained)
{
    assert(desired);
    SDL_Aout_Opaque *opaque = aout->opaque;

    opaque->spec = *desired;
//    opaque->atrack = SDL_Android_AudioTrack_new_from_sdl_spec(env, desired);
//    if (!opaque->atrack) {
//        ALOGE("aout_open_audio_n: failed to new AudioTrcak()");
//        return -1;
//    }
    QAudioFormat fmt;
    
#if defined(QT6)
    opaque->devices = new QMediaDevices();
    const QAudioDevice &device = opaque->devices->defaultAudioOutput();
    
    fmt.setSampleRate(desired->freq);
    fmt.setChannelCount(desired->channels);
    fmt.setSampleFormat(QAudioFormat::SampleFormat::Int16);

#else
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultOutputDevice();
    fmt.setSampleRate(desired->freq);
    fmt.setChannelCount(desired->channels);
    fmt.setSampleSize(16);
    fmt.setCodec("audio/pcm");
    fmt.setByteOrder(QAudioFormat::LittleEndian);
    fmt.setSampleType(QAudioFormat::SignedInt);
    
#endif

    if(device.isFormatSupported(fmt)) {
        
        if (obtained) {
            obtained->freq = fmt.sampleRate();
            obtained->channels = fmt.channelCount();
            obtained->format = AUDIO_S16SYS;
        }
        
//        opaque->provider = new AudioDataProvider(fmt, 1000000, 600);
//        opaque->provider->start();
//
//        opaque->buffer_size = 4096;
//        opaque->audio->setBufferSize(opaque->buffer_size);
//
//        opaque->audio->start(opaque->provider);
//
//        opaque->buffer_size = opaque->audio->bufferSize();
//        opaque->buffer = (uint8_t *)malloc(opaque->buffer_size);
        
        opaque->thread = new MyAudioThread(aout, fmt);
        opaque->thread->start();
   
        opaque->pause_on = 1;
        opaque->abort_request = 0;
        
    } else {
        
    }
    
//    opaque->buffer_size = SDL_Android_AudioTrack_get_min_buffer_size(opaque->atrack);
//    if (opaque->buffer_size <= 0) {
//        ALOGE("aout_open_audio_n: failed to getMinBufferSize()");
//        SDL_Android_AudioTrack_free(env, opaque->atrack);
//        opaque->atrack = NULL;
//        return -1;
//    }

//    opaque->buffer = malloc(opaque->buffer_size);
//    if (!opaque->buffer) {
//        ALOGE("aout_open_audio_n: failed to allocate buffer");
//        SDL_Android_AudioTrack_free(env, opaque->atrack);
//        opaque->atrack = NULL;
//        return -1;
//    }



//    opaque->audio_session_id = SDL_Android_AudioTrack_getAudioSessionId(env, opaque->atrack);
//    ALOGI("audio_session_id = %d\n", opaque->audio_session_id);


//    opaque->audio_tid = SDL_CreateThreadEx(&opaque->_audio_tid, aout_thread, aout, "ff_aout_qt");
//    if (!opaque->audio_tid) {
//        ALOGE("aout_open_audio_n: failed to create audio thread");
//        SDL_Android_AudioTrack_free(env, opaque->atrack);
//        opaque->atrack = NULL;
//        return -1;
//    }

    return 0;
}

static void aout_pause_audio(SDL_Aout *aout, int pause_on)
{
    SDLTRACE("aout_pause_audio(%d)\n", pause_on);
    SDL_Aout_Opaque *opaque = aout->opaque;
    opaque->pause_on = pause_on;
     if (pause_on) {
         
     } else {
         
     }
}

static void aout_flush_audio(SDL_Aout *aout)
{
    SDLTRACE("aout_flush_audio()\n");
    SDL_Aout_Opaque *opaque = aout->opaque;

    // [opaque->aoutController flush];
}

static void aout_close_audio(SDL_Aout *aout)
{
    SDLTRACE("aout_close_audio()\n");
    SDL_Aout_Opaque *opaque = aout->opaque;

    // [opaque->aoutController close];
}

static void aout_set_playback_rate(SDL_Aout *aout, float playbackRate)
{
    SDLTRACE("aout_close_audio()\n");
    SDL_Aout_Opaque *opaque = aout->opaque;

    // [opaque->aoutController setPlaybackRate:playbackRate];
}

static void aout_set_playback_volume(SDL_Aout *aout, float volume)
{
    SDLTRACE("aout_set_volume()\n");
    SDL_Aout_Opaque *opaque = aout->opaque;

    // [opaque->aoutController setPlaybackVolume:volume];
}

static double auout_get_latency_seconds(SDL_Aout *aout)
{
    SDL_Aout_Opaque *opaque = aout->opaque;
    return 0;//[opaque->aoutController get_latency_seconds];
}

static int aout_get_persecond_callbacks(SDL_Aout *aout)
{
    return SDL_QT_AUDIO_MAX_CALLBACKS_PER_SEC;
}

static void aout_free_l(SDL_Aout *aout)
{
    if (!aout)
        return;

    aout_close_audio(aout);

    SDL_Aout_Opaque *opaque = aout->opaque;
    if (opaque) {
        // [opaque->aoutController release];
        // opaque->aoutController = nil;
    }

    SDL_Aout_FreeInternal(aout);
}

SDL_Aout *SDL_Aout_Qt_Create()
{
    SDL_Aout *aout = SDL_Aout_CreateInternal(sizeof(SDL_Aout_Opaque));
    if (!aout)
        return NULL;

    SDL_Aout_Opaque *opaque = aout->opaque;
    opaque->wakeup_cond  = SDL_CreateCond();
    opaque->wakeup_mutex = SDL_CreateMutex();
    opaque->speed        = 1.0f;

    aout->free_l = aout_free_l;
    aout->open_audio  = aout_open_audio;
    aout->pause_audio = aout_pause_audio;
    aout->flush_audio = aout_flush_audio;
    aout->close_audio = aout_close_audio;

    aout->func_set_playback_rate = aout_set_playback_rate;
    aout->func_set_playback_volume = aout_set_playback_volume;
    aout->func_get_latency_seconds = auout_get_latency_seconds;
    aout->func_get_audio_persecond_callbacks = aout_get_persecond_callbacks;
    return aout;
}

AudioDataProvider::AudioDataProvider(const QAudioFormat &format, qint64 durationUs, int sampleRate)
{
    if (format.isValid())
        generateData(format, durationUs, sampleRate);
}

void AudioDataProvider::start()
{
    open(QIODevice::ReadOnly);
}

void AudioDataProvider::stop()
{
    m_pos = 0;
    close();
}

void AudioDataProvider::generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate)
{
    const int channelBytes = format.bytesPerFrame();
    const int sampleBytes = format.channelCount() * channelBytes;
    qint64 length = format.bytesForDuration(durationUs);
    Q_ASSERT(length % sampleBytes == 0);
    Q_UNUSED(sampleBytes); // suppress warning in release builds

    m_buffer.resize(length);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buffer.data());
    int sampleIndex = 0;

//    while (length) {
//        // Produces value (-1..1)
//        const qreal x = qSin(2 * M_PI * sampleRate * qreal(sampleIndex++ % format.sampleRate()) / format.sampleRate());
//        for (int i=0; i<format.channelCount(); ++i) {
//            switch(format.sampleFormat()) {
//            case QAudioFormat::UInt8:
//                *reinterpret_cast<quint8 *>(ptr) = static_cast<quint8>((1.0 + x) / 2 * 255);
//                break;
//            case QAudioFormat::Int16:
//                *reinterpret_cast<qint16 *>(ptr) = static_cast<qint16>(x * 32767);
//                break;
//            case QAudioFormat::Int32:
//                *reinterpret_cast<qint32 *>(ptr) = static_cast<qint32>(x * std::numeric_limits<qint32>::max());
//                break;
//            case QAudioFormat::Float:
//                *reinterpret_cast<float *>(ptr) = x;
//                break;
//            default:
//                break;
//            }
//
//            ptr += channelBytes;
//            length -= channelBytes;
//        }
//    }
}

qint64 AudioDataProvider::readData(char *data, qint64 len)
{
    qint64 total = 0;
    if (!m_buffer.isEmpty()) {
        while (len - total > 0) {
            const qint64 chunk = qMin((m_buffer.size() - m_pos), len - total);
            memcpy(data + total, m_buffer.constData() + m_pos, chunk);
            m_pos = (m_pos + chunk) % m_buffer.size();
            total += chunk;
        }
    }
    return total;
}

qint64 AudioDataProvider::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 AudioDataProvider::bytesAvailable() const
{
    return m_buffer.size() + QIODevice::bytesAvailable();
}


MyAudioThread::MyAudioThread(SDL_Aout *aout, const QAudioFormat &format, QObject *parent):
aout_(aout),
format_(format)
{
    
}

void MyAudioThread::run() {
    
    SDL_Aout *aout = (SDL_Aout *)aout_;
    SDL_Aout_Opaque *opaque = aout->opaque;
#if defined(QT6)
    const QAudioDevice &device = opaque->devices->defaultAudioOutput();
    opaque->audio = new QAudioSink(device, format_);
#else
    opaque->audio = new QAudioOutput(format_);
#endif
    
    opaque->buffer_size = 4096;
    opaque->audio->setBufferSize((int)opaque->buffer_size);

    //opaque->audio->start(opaque->provider);
    opaque->io = opaque->audio->start();
    
    opaque->buffer_size = opaque->audio->bufferSize();
    opaque->buffer = (uint8_t *)malloc(opaque->buffer_size);
    
    
    SDL_AudioCallback audio_cblk = opaque->spec.callback;
    void *userdata = opaque->spec.userdata;
    uint8_t *buffer = opaque->buffer;
    size_t copy_size = 0;

    assert(opaque->io);
    assert(buffer);
    
    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);

    if (!opaque->abort_request && !opaque->pause_on){
//        SDL_Android_AudioTrack_play(env, atrack);
    }


    while (!opaque->abort_request) {
        SDL_LockMutex(opaque->wakeup_mutex);
        if (!opaque->abort_request && opaque->pause_on) {
//            SDL_Android_AudioTrack_pause(env, atrack);
            while (!opaque->abort_request && opaque->pause_on) {
                SDL_CondWaitTimeout(opaque->wakeup_cond, opaque->wakeup_mutex, 1000);
            }
            if (!opaque->abort_request && !opaque->pause_on) {
                if (opaque->need_flush) {
                    opaque->need_flush = 0;
//                    SDL_Android_AudioTrack_flush(env, atrack);
                }
//                SDL_Android_AudioTrack_play(env, atrack);
            }
        }
        if (opaque->need_flush) {
            opaque->need_flush = 0;
//            SDL_Android_AudioTrack_flush(env, atrack);
        }
        if (opaque->need_set_volume) {
            opaque->need_set_volume = 0;
//            SDL_Android_AudioTrack_set_volume(env, atrack, opaque->left_volume, opaque->right_volume);
        }
        if (opaque->speed_changed) {
            opaque->speed_changed = 0;
//            SDL_Android_AudioTrack_setSpeed(env, atrack, opaque->speed);
        }
        SDL_UnlockMutex(opaque->wakeup_mutex);
        
//        if (audio->state() == QAudio::SuspendedState || audio->state() == QAudio::StoppedState) {
//            audio->resume();
//        } else if (audio->state() == QAudio::ActiveState) {
//            audio->suspend();
//        } else if (audio->state() == QAudio::IdleState) {
//            // no-op
//        }
        
        copy_size = opaque->audio->bytesFree();
        //printf("status = %d, copy size = %lld \n", opaque->audio->state(), copy_size);
        audio_cblk(userdata, buffer, (int)copy_size);
        if (opaque->need_flush) {
//            SDL_Android_AudioTrack_flush(env, atrack);
            opaque->need_flush = false;
        }

        if (opaque->need_flush) {
            opaque->need_flush = 0;
//            SDL_Android_AudioTrack_flush(env, atrack);
        } else {
//            int written = SDL_Android_AudioTrack_write(env, atrack, buffer, copy_size);
//            if (written != copy_size) {
//                ALOGW("AudioTrack: not all data copied %d/%d", (int)written, (int)copy_size);
//            }
            if(copy_size > 0) {
                opaque->io->write((const char *)buffer, (qint64)copy_size);
                
                static FILE *file = fopen("/Users/chenxiangyu/Documents/4035d397-17db85911c1.mov.pcm", "wb+");
                if(file) {
                    fwrite(buffer, 1, copy_size, file);
                }
            }
        }
        
        av_usleep(10 * 1000);
        //exec();
        // TODO: 1 if callback return -1 or 0
    }

//    SDL_Android_AudioTrack_free(env, atrack);
    
}
