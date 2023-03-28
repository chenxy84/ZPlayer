package tv.danmaku.ijk.media.player.widget;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.aliyun.player.source.UrlSource;
import tv.danmaku.ijk.media.player.PlayerQosInfo;

public abstract class AbstractPlayerView extends FrameLayout {

    public AbstractPlayerView(@NonNull Context context) {
        super(context);
    }

    public AbstractPlayerView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public AbstractPlayerView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }


    public abstract void setSurfaceType(AliyunRenderView.SurfaceType surfaceType);
    public abstract void setDataSource(UrlSource urlSource);
    public abstract void setAutoPlay(boolean isAutoPlay);
    public abstract void prepare();
    public abstract void start();
    public abstract void reload();
    public abstract void pause();
    public abstract void stop();
    public abstract void release();


    public abstract void seekTo(long msec);
    public abstract long getCurrentPosition();
    public abstract void setLoop(boolean enable);

    public abstract PlayerQosInfo getQosInfo();

    public abstract void setVolume(int channel, float volume);
    public abstract void setVolume(float volume);

}
