package tv.danmaku.ijk.media.player.widget;

import android.view.Surface;
import android.view.View;

public interface IRenderView {

    void addRenderCallback(IRenderCallback renderCallback);

    View getView();

    void setVideoSize(int width, int height);

    public interface IRenderCallback{
        void onSurfaceCreate(Surface surface);

        void onSurfaceChanged(int width, int height);

        void onSurfaceDestroyed();
    }
}
