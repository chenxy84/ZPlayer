package tv.danmaku.ijk.media.player.widget;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

public class IJKSurfaceRenderView extends SurfaceView implements IRenderView, SurfaceHolder.Callback{

    private IRenderCallback mRenderCallback;
    private IJKMeasureHelper mMeasureHelper;

    public IJKSurfaceRenderView(Context context) {
        super(context);
        init(context);
    }

    public IJKSurfaceRenderView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public IJKSurfaceRenderView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private void init(Context context) {
        mMeasureHelper = new IJKMeasureHelper(this);
        Log.e("IJKSurfaceRenderView", "init: SurfaceRenderView");
        getHolder().addCallback(this);
    }

    @Override
    public void addRenderCallback(IRenderCallback renderCallback) {
        this.mRenderCallback = renderCallback;
    }

    @Override
    public View getView() {
        return this;
    }

    @Override
    public void setVideoSize(int width, int height) {
        if(mMeasureHelper != null) {
            mMeasureHelper.setVideoSize(width, height);
        }
        requestLayout();
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        if(mRenderCallback != null){
            mRenderCallback.onSurfaceCreate(surfaceHolder.getSurface());
        }
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        //maybe need test
        mMeasureHelper.setAspectRatio(IJKMeasureHelper.AR_ASPECT_FILL_PARENT);
        mMeasureHelper.doMeasure(widthMeasureSpec, heightMeasureSpec);
        setMeasuredDimension(mMeasureHelper.getMeasuredWidth(), mMeasureHelper.getMeasuredHeight());
    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int format, int width, int height) {

        if(mRenderCallback != null){
            mRenderCallback.onSurfaceChanged(width,height);
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
        Surface surface = surfaceHolder.getSurface();
        if(surface != null){
            surface.release();
        }
        if(mRenderCallback != null){
            mRenderCallback.onSurfaceDestroyed();
        }
    }
}
