package tv.danmaku.ijk.media.player.widget;

import android.content.Context;
import android.net.Uri;
import android.os.Build;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.widget.FrameLayout;

import com.aliyun.player.IPlayer;
import com.aliyun.player.nativeclass.CacheConfig;
import com.aliyun.player.nativeclass.MediaInfo;
import com.aliyun.player.nativeclass.PlayerConfig;
import com.aliyun.player.nativeclass.TrackInfo;
import com.aliyun.player.source.UrlSource;


import java.io.IOException;
import java.lang.ref.WeakReference;
import java.util.Arrays;

import tv.danmaku.ijk.media.player.BuildConfig;
import tv.danmaku.ijk.media.player.IMediaPlayer;
import tv.danmaku.ijk.media.player.IjkMediaPlayer;
import tv.danmaku.ijk.media.player.IjkTimedText;
import tv.danmaku.ijk.media.player.PlayerQosInfo;

public class IjkVideoView extends AbstractPlayerView {

    private String TAG = "IjkVideoView";

    private Context mContext;
    /**
     * 真正的播放器实例对象
     */
    private IMediaPlayer mPlayer;
    private String mUri;
    /**
     * Surface
     */
    private IRenderView mIRenderView;


    public IRenderView getIRenderView() {
        return mIRenderView;
    }

    /**
     * 判断当前解码状态,true:硬解,false:软解
     * 默认是硬解
     */
    private boolean mCurrentEnableHardwareDecoder = true;

    private Surface mSurface;
    private boolean isNeedPrepared;

    private int mVideoSarNum;
    private int mVideoSarDen;
    private int mVideoWidth;
    private int mVideoHeight;
    private int mSurfaceWidth;
    private int mSurfaceHeight;

    public IjkVideoView(Context context) {
        super(context);
        init(context);
    }

    public IjkVideoView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public IjkVideoView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private void init(Context context) {
        this.mContext = context;
        initPlayer();
    }

    private void initPlayer() {
        mPlayer = new IjkMediaPlayer();
        initPlayerListener();
    }

    private void initPlayerListener() {
        mPlayer.setOnPreparedListener(mPreparedListener);
        mPlayer.setOnVideoSizeChangedListener(mSizeChangedListener);
        mPlayer.setOnCompletionListener(mCompletionListener);
        mPlayer.setOnErrorListener(mErrorListener);
        mPlayer.setOnInfoListener(mInfoListener);
        mPlayer.setOnBufferingUpdateListener(mBufferingUpdateListener);
        mPlayer.setOnSeekCompleteListener(mSeekCompleteListener);
//        mPlayer.setOnTimedTextListener(mTimedTextListener);
    }

    public enum SurfaceType {
        /**
         * TextureView
         */
        TEXTURE_VIEW,
        /**
         * SurfacView
         */
        SURFACE_VIEW
    }

    public Surface getSurface() {
        return mSurface;
    }

    /**
     * 获取真正的播放器实例对象
     */
    public IMediaPlayer getIjkPlayer() {
        return mPlayer;
    }

    /**
     * 该方法需要在创建播放器完成后,prepare前调用
     *
     * @param surfaceType Surface的类型
     */
    public void setSurfaceType(AliyunRenderView.SurfaceType surfaceType) {
        if (surfaceType == AliyunRenderView.SurfaceType.TEXTURE_VIEW && (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH)) {
            mIRenderView = new TextureRenderView(mContext);
        } else {
            mIRenderView = new IJKSurfaceRenderView(mContext);
        }
        initListener();
        addView(mIRenderView.getView());
    }

    private static class MyRenderViewCallback implements IRenderView.IRenderCallback {

        private WeakReference<IjkVideoView> weakReference;

        private MyRenderViewCallback(IjkVideoView ijkVideoView) {
            weakReference = new WeakReference<>(ijkVideoView);
        }

        @Override
        public void onSurfaceCreate(Surface surface) {
            IjkVideoView ijkVideoView = weakReference.get();
            if (ijkVideoView != null && ijkVideoView.mPlayer != null) {
                ijkVideoView.mSurface = surface;
                ijkVideoView.mPlayer.setSurface(surface);
                if(ijkVideoView.isNeedPrepared) {
                    ijkVideoView.prepare();
                }
            }
        }

        @Override
        public void onSurfaceChanged(int width, int height) {
            IjkVideoView ijkVideoView = weakReference.get();
            if (ijkVideoView != null && ijkVideoView.mPlayer != null) {
//              ijkVideoView.mPlayer.surfaceChanged();

            }
        }

        @Override
        public void onSurfaceDestroyed() {
            IjkVideoView ijkVideoView = weakReference.get();
            if (ijkVideoView != null && ijkVideoView.mPlayer != null) {
                ijkVideoView.mPlayer.setSurface(null);
            }
        }
    }

    /**
     * 设置播放源
     */
    public void setDataSource(Uri uri) {
//        if (mPlayer != null) {
//            try {
//                mPlayer.setDataSource(mContext, uri);
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }
        this.setDataSource(uri.toString());
    }

    /**
     * 设置播放源
     */
    public void setDataSource(String uri) {
        if (mPlayer != null) {
            try {
                mUri = uri;
                mPlayer.setDataSource(uri);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 设置播放源
     */
    public void setDataSource(UrlSource urlSource) {
//        if (mPlayer != null) {
//            try {
//                mPlayer.setDataSource(urlSource.getUri());
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }
        this.setDataSource(urlSource.getUri());
    }

    /**
     * 设置是否静音
     */
    public void setMute(boolean isMute) {
        if (mPlayer != null) {
            //mPlayer.setMute(isMute);
        }
    }

    /**
     * 设置音量
     */
    @Override
    public void setVolume(float v) {
        if (mPlayer != null) {
//            mPlayer.setVolume(v);
        }
    }

    @Override
    public void setVolume(int c, float v) {
        if (mPlayer != null) {
            mPlayer.setVolume(c, v);
        }
    }

    /**
     * 获取音量
     */
    public float getVolume() {
        if (mPlayer != null) {
//            return mPlayer.getVolume();
        }
        return 0;
    }

    /**
     * 是否开启自动播放
     */
    public void setAutoPlay(boolean isAutoPlay) {
        if (mPlayer != null) {
            ((IjkMediaPlayer)mPlayer).setOption(IjkMediaPlayer.OPT_CATEGORY_PLAYER, "start-on-prepared", isAutoPlay?1:0);
        }
    }

    /**
     * 设置播放速率
     */
//    public void setSpeed(float speed) {
//        if (mAliPlayer != null) {
//            mAliPlayer.setSpeed(speed);
//        }
//    }

    /**
     * 是否循环播放
     */
    @Override
    public void setLoop(boolean loop) {
        if (mPlayer != null) {
            mPlayer.setLooping(loop);
        }
    }

    public boolean isLoop() {
        if (mPlayer != null) {
            return mPlayer.isLooping();
        }
        return false;
    }

    /**
     * 截屏
     */
//    public void snapshot() {
//        if (mAliPlayer != null) {
//            mAliPlayer.snapshot();
//        }
//    }

    /**
     * 选择 track
     *
     * @param index 索引
     */
    public void selectTrack(int index) {
        if (mPlayer != null) {
            //TODO
        }
    }

    /**
     * 选择 track
     *
     * @param index 索引
     * @param focus 是否强制选择track
     */
    public void selectTrack(int index, boolean focus) {
//        if (mAliPlayer != null) {
//            mAliPlayer.selectTrack(index, focus);
//        }
    }

    /**
     * 停止播放
     */
    public void stop() {
        if (mPlayer != null) {
            mPlayer.stop();
        }
    }

    /**
     * prepare
     */
    public void prepare() {
        if (mPlayer != null) {
            if (mSurface != null) {
                mPlayer.prepareAsync();
                isNeedPrepared = false;
            } else {
                isNeedPrepared = true;
            }

        }
    }

    /**
     * 暂停播放,直播流不建议使用
     */
    public void pause() {
        if (mPlayer != null) {
            mPlayer.pause();
            isNeedPrepared = false;
        }
    }

    public void start() {
        if (mPlayer != null) {
            mPlayer.start();
        }
    }

//    public void stopPlayback() {
//        if (mPlayer != null) {
//            mPlayer.stop();
//            mPlayer.release();
//            mPlayer = null;
//            AudioManager am = (AudioManager) mContext.getSystemService(Context.AUDIO_SERVICE);
//            am.abandonAudioFocus(null);
//        }
//    }

    public void reload() {

        long currentDuration = getDuration();
        Log.i(TAG, "IJKVideoView reload: " + currentDuration);

        if (mPlayer != null) {
            //mPlayer.reload()
            isNeedPrepared = false;
            mPlayer.stop();
            mPlayer.release();
            mPlayer = null;
        }
        this.initPlayer();

        try {
            mPlayer.setDataSource(mUri);
        } catch (IOException e) {
            Log.e(TAG,"IJKVideoView reload setDataSource failed: " + mUri);
        }
        mPlayer.setSurface(mSurface);

        this.prepare();
        //this.seekTo(currentDuration);
    }

    /**
     * 获取视频时长
     */
    public long getDuration() {
        if (mPlayer != null) {
            return mPlayer.getDuration();
        }
        return 0;
    }

    /**
     * 获取当前 track
     */
//    public TrackInfo currentTrack(TrackInfo.Type typeVideo) {
//        if (mPlayer != null) {
//            return mPlayer.currentTrack(typeVideo);
//        }
//        return null;
//    }

    /**
     * 获取当前 track
     */
    @Deprecated
    public TrackInfo currentTrack(int ordinal) {
//        if (mAliPlayer != null) {
//            return mAliPlayer.currentTrack(ordinal);
//        }
        return null;
    }

    /**
     * seek
     *
     * @param position 目标位置
     */
    public void seekTo(long position) {
        if (position == 0) {
            Log.d(TAG, "IJKVideoView seek to " + position);
        }
        if (mPlayer != null) {
            mPlayer.seekTo(position);
        }
    }

    private void initListener() {
        mIRenderView.addRenderCallback(new IjkVideoView.MyRenderViewCallback(this));
    }

    public long getCurrentPosition() {
        if(mPlayer != null) {
            return mPlayer.getCurrentPosition();
        } else {
            return 0l;
        }
    }

    /**
     * 缓存配置
     */
    public void setCacheConfig(CacheConfig cacheConfig) {
//        if (mAliPlayer != null) {
//            mAliPlayer.setCacheConfig(cacheConfig);
//        }
    }

    /**
     * 设置PlayerConfig
     */
    public void setPlayerConfig(PlayerConfig playerConfig) {
//        if (mAliPlayer != null) {
//            mAliPlayer.setConfig(playerConfig);
//        }
    }

    /**
     * 获取PlayerConfig
     */
    public PlayerConfig getPlayerConfig() {
//        if (mAliPlayer != null) {
//            return mAliPlayer.getConfig();
//        }
        return null;
    }

    /**
     * 设置缩放模式
     */
    public void setScaleModel(IPlayer.ScaleMode scaleMode) {
//        if (mAliPlayer != null) {
//            mAliPlayer.setScaleMode(scaleMode);
//        }
    }

    /**
     * 获取当前缩放模式
     */
    public IPlayer.ScaleMode getScaleModel() {
//        if (mAliPlayer != null) {
//            return mAliPlayer.getScaleMode();
//        }
        return IPlayer.ScaleMode.SCALE_ASPECT_FIT;
    }

    /**
     * 设置旋转模式
     */
    public void setRotateModel(IPlayer.RotateMode rotateModel) {
//        if (mAliPlayer != null) {
//            mAliPlayer.setRotateMode(rotateModel);
//        }
    }

    /**
     * 获取当前旋转模式
     */
    public IPlayer.RotateMode getRotateModel() {
//        if (mAliPlayer != null) {
//            return mAliPlayer.getRotateMode();
//        }
        return IPlayer.RotateMode.ROTATE_0;
    }

    /**
     * 设置镜像模式
     */
    public void setMirrorMode(IPlayer.MirrorMode mirrorMode) {
//        if (mAliPlayer != null) {
//            mAliPlayer.setMirrorMode(mirrorMode);
//        }
    }

    /**
     * 获取当前镜像模式
     */
    public IPlayer.MirrorMode getMirrorMode() {
//        if (mAliPlayer != null) {
//            return mAliPlayer.getMirrorMode();
//        }
        return IPlayer.MirrorMode.MIRROR_MODE_NONE;
    }

    public MediaInfo getMediaInfo() {
//        if (mAliPlayer != null) {
//            return mAliPlayer.getMediaInfo();
//        }
        return null;
    }

    /**
     * 软硬解开关
     *
     * @param enableHardwareDecoder true:硬解,false:软解
     */
    public void enableHardwareDecoder(boolean enableHardwareDecoder) {
//        if (mAliPlayer != null) {
//            mCurrentEnableHardwareDecoder = enableHardwareDecoder;
//            mAliPlayer.enableHardwareDecoder(enableHardwareDecoder);
//        }
    }

    /**
     * 获取当前解码状态
     *
     * @return true:硬解,false:软解
     */
    public boolean isHardwareDecoder() {
        return mCurrentEnableHardwareDecoder;
    }

    public void release() {
        if(mPlayer != null) {
            mPlayer.stop();

            mPlayer.setOnPreparedListener(null);
            mPlayer.setOnVideoSizeChangedListener(null);
            mPlayer.setOnCompletionListener(null);
            mPlayer.setOnErrorListener(null);
            mPlayer.setOnInfoListener(null);
            mPlayer.setOnBufferingUpdateListener(null);
            mPlayer.setOnSeekCompleteListener(null);

            mPlayer.setSurface(null);

            mPlayer.release();
            mPlayer = null;

            mOnCompletionListener = null;
            mOnPreparedListener = null;
            mOnSeekCompleteListener = null;
            mOnErrorListener = null;
            mOnInfoListener = null;
            mOnVideoSizeChangeListener = null;
            mOnBufferingUpdateListener = null;
        }
        mSurface = null;
    }

    public void setOnCompletionListener(IMediaPlayer.OnCompletionListener onCompletionListener) {
        this.mOnCompletionListener = onCompletionListener;
    }

    public void setOnPreparedListener(IMediaPlayer.OnPreparedListener onPreparedListener) {
        this.mOnPreparedListener = onPreparedListener;
    }

    public void setOnSeekCompleteListener(IMediaPlayer.OnSeekCompleteListener onSeekCompleteListener) {
        this.mOnSeekCompleteListener = onSeekCompleteListener;
    }

    public void setOnErrorListener(IMediaPlayer.OnErrorListener onErrorListener) {
        this.mOnErrorListener = onErrorListener;
    }

    public void setOnInfoListener(IMediaPlayer.OnInfoListener onInfoListener) {
        this.mOnInfoListener = onInfoListener;
    }

    public void setmOnVideoSizeChangeListener(IMediaPlayer.OnVideoSizeChangedListener onVideoSizeChangeListener) {
        this.mOnVideoSizeChangeListener = onVideoSizeChangeListener;
    }

    public void setmOnBufferingUpdateListener(IMediaPlayer.OnBufferingUpdateListener onBufferingUpdateListener) {
        this.mOnBufferingUpdateListener = onBufferingUpdateListener;
    }

    private IMediaPlayer.OnCompletionListener mOnCompletionListener;
    private IMediaPlayer.OnPreparedListener mOnPreparedListener;
    private IMediaPlayer.OnErrorListener mOnErrorListener;
    private IMediaPlayer.OnInfoListener mOnInfoListener;
    private IMediaPlayer.OnVideoSizeChangedListener mOnVideoSizeChangeListener;
    private IMediaPlayer.OnBufferingUpdateListener mOnBufferingUpdateListener;
    private IMediaPlayer.OnSeekCompleteListener mOnSeekCompleteListener;


    IMediaPlayer.OnVideoSizeChangedListener mSizeChangedListener =
            new IMediaPlayer.OnVideoSizeChangedListener() {
                public void onVideoSizeChanged(IMediaPlayer mp, int width, int height, int sarNum, int sarDen) {
                    mVideoWidth = mp.getVideoWidth();
                    mVideoHeight = mp.getVideoHeight();
                    mVideoSarNum = mp.getVideoSarNum();
                    mVideoSarDen = mp.getVideoSarDen();
                    if (mVideoWidth != 0 && mVideoHeight != 0) {
                        if (IjkVideoView.this.mIRenderView != null) {
                            IjkVideoView.this.mIRenderView.setVideoSize(mVideoWidth, mVideoHeight);
                            //IjkVideoView.this.mIRenderView.setVideoSampleAspectRatio(mVideoSarNum, mVideoSarDen);
                            //IjkVideoView.this.requestLayout();
                        }
                        // REMOVED: getHolder().setFixedSize(mVideoWidth, mVideoHeight);

                    }
                    if (mOnVideoSizeChangeListener != null) {
                        mOnVideoSizeChangeListener.onVideoSizeChanged(mp, width, height, sarNum, sarDen);
                    }
                }
            };

    IMediaPlayer.OnPreparedListener mPreparedListener = new IMediaPlayer.OnPreparedListener() {
        public void onPrepared(IMediaPlayer mp) {

            if (mOnPreparedListener != null) {
                mOnPreparedListener.onPrepared(mPlayer);
            }

            mVideoWidth = mp.getVideoWidth();
            mVideoHeight = mp.getVideoHeight();

        }
    };

    private IMediaPlayer.OnCompletionListener mCompletionListener =
            new IMediaPlayer.OnCompletionListener() {
                public void onCompletion(IMediaPlayer mp) {
                    if (mOnCompletionListener != null) {
                        mOnCompletionListener.onCompletion(mPlayer);
                    }
                }
            };

    static private long currentTimeMillis = System.currentTimeMillis();
    private IMediaPlayer.OnInfoListener mInfoListener =
            new IMediaPlayer.OnInfoListener() {
                public boolean onInfo(IMediaPlayer mp, int arg1, int arg2) {
                    if (mOnInfoListener != null) {
                        mOnInfoListener.onInfo(mp, arg1, arg2);
                    }
                    switch (arg1) {
                        case IMediaPlayer.MEDIA_INFO_VIDEO_TRACK_LAGGING:
                            Log.d(TAG, "MEDIA_INFO_VIDEO_TRACK_LAGGING:");
                            break;
                        case IMediaPlayer.MEDIA_INFO_VIDEO_RENDERING_START:
                            Log.d(TAG, "MEDIA_INFO_VIDEO_RENDERING_START:");
                            break;
                        case IMediaPlayer.MEDIA_INFO_BUFFERING_START:
                            Log.d(TAG, "MEDIA_INFO_BUFFERING_START:");
                            break;
                        case IMediaPlayer.MEDIA_INFO_BUFFERING_END:
                            Log.d(TAG, "MEDIA_INFO_BUFFERING_END:");
                            break;
                        case IMediaPlayer.MEDIA_INFO_NETWORK_BANDWIDTH:
                            Log.d(TAG, "MEDIA_INFO_NETWORK_BANDWIDTH: " + arg2);
                            break;
                        case IMediaPlayer.MEDIA_INFO_BAD_INTERLEAVING:
                            Log.d(TAG, "MEDIA_INFO_BAD_INTERLEAVING:");
                            break;
                        case IMediaPlayer.MEDIA_INFO_NOT_SEEKABLE:
                            Log.d(TAG, "MEDIA_INFO_NOT_SEEKABLE:");
                            break;
                        case IMediaPlayer.MEDIA_INFO_METADATA_UPDATE:
                            Log.d(TAG, "MEDIA_INFO_METADATA_UPDATE:");
                            break;
                        case IMediaPlayer.MEDIA_INFO_UNSUPPORTED_SUBTITLE:
                            Log.d(TAG, "MEDIA_INFO_UNSUPPORTED_SUBTITLE:");
                            break;
                        case IMediaPlayer.MEDIA_INFO_SUBTITLE_TIMED_OUT:
                            Log.d(TAG, "MEDIA_INFO_SUBTITLE_TIMED_OUT:");
                            break;
                        case IMediaPlayer.MEDIA_INFO_VIDEO_ROTATION_CHANGED:
                            Log.d(TAG, "MEDIA_INFO_VIDEO_ROTATION_CHANGED: " + arg2);
                            break;
//                        case IMediaPlayer.MEDIA_INFO_MEDIA_CURRENT_POSITION:
//                            //Log.d(TAG, "MEDIA_INFO_MEDIA_CURRENT_POSITION: " + arg2);
//                            if(BuildConfig.DEBUG) {
//                                long now = System.currentTimeMillis();
//                                if (now - currentTimeMillis > 2000) {
//                                    Log.i(TAG, getQosInfo().toString());
//                                    currentTimeMillis = now;
//                                }
//                            }
//                            break;
                        case IMediaPlayer.MEDIA_INFO_AUDIO_RENDERING_START:
                            Log.d(TAG, "MEDIA_INFO_AUDIO_RENDERING_START:");
                            break;
                    }
                    return true;
                }
            };

    private IMediaPlayer.OnErrorListener mErrorListener =
            new IMediaPlayer.OnErrorListener() {
                public boolean onError(IMediaPlayer mp, int framework_err, int impl_err) {
                    Log.d(TAG, "Error: " + framework_err + "," + impl_err);

                    /* If an error handler has been supplied, use it and finish. */
                    if (mOnErrorListener != null) {
                        if (mOnErrorListener.onError(mPlayer, framework_err, impl_err)) {
                            return true;
                        }
                    }
                    return true;
                }
            };

    private IMediaPlayer.OnBufferingUpdateListener mBufferingUpdateListener =
            new IMediaPlayer.OnBufferingUpdateListener() {
                public void onBufferingUpdate(IMediaPlayer mp, int percent) {
                    if(mOnBufferingUpdateListener != null) {
                        mOnBufferingUpdateListener.onBufferingUpdate(mp, percent);
                    }
                }
            };

    private IMediaPlayer.OnSeekCompleteListener mSeekCompleteListener =
            new IMediaPlayer.OnSeekCompleteListener() {
                @Override
                public void onSeekComplete(IMediaPlayer mp) {
                    if(mOnSeekCompleteListener != null) {
                        mOnSeekCompleteListener.onSeekComplete(mp);
                    }
                }
    };

    private IMediaPlayer.OnTimedTextListener mTimedTextListener = new IMediaPlayer.OnTimedTextListener() {
        @Override
        public void onTimedText(IMediaPlayer mp, IjkTimedText text) {

        }
    };

    public PlayerQosInfo getQosInfo() {
        if(mPlayer != null) {
            PlayerQosInfo qosInfo = new PlayerQosInfo();
            qosInfo.height = mPlayer.getVideoHeight();
            qosInfo.width = mPlayer.getVideoWidth();

            if(mPlayer.getClass().isInstance(IjkMediaPlayer.class)) {
                IjkMediaPlayer p = (IjkMediaPlayer) mPlayer;
                qosInfo.vfps = p.getVideoOutputFramesPerSecond();
                qosInfo.vdps = p.getVideoDecodeFramesPerSecond();
            }

        }
        return null;
    }

}

