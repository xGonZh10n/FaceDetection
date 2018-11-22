package com.lightweh.facedetection;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PixelFormat;
import android.graphics.PorterDuff;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.lightweh.dlib.VisionDetRet;

import java.util.List;

public class BoundingBoxView extends SurfaceView implements SurfaceHolder.Callback {

    protected SurfaceHolder mSurfaceHolder;

    private Paint mPaint;

    private boolean mIsCreated;

    public BoundingBoxView(Context context, AttributeSet attrs) {
        super(context, attrs);

        mSurfaceHolder = getHolder();
        mSurfaceHolder.addCallback(this);
        mSurfaceHolder.setFormat(PixelFormat.TRANSPARENT);
        setZOrderOnTop(true);

        mPaint = new Paint();
        mPaint.setAntiAlias(true);
        mPaint.setColor(Color.RED);
        mPaint.setStrokeWidth(5f);
        mPaint.setStyle(Paint.Style.STROKE);


    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int format, int width, int height) {
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        mIsCreated = true;
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
        mIsCreated = false;
    }

    public void setResults(List<VisionDetRet> detRets)
    {
        if (!mIsCreated) {
            return;
        }

        Canvas canvas = mSurfaceHolder.lockCanvas();

        //清除掉上一次的画框。
        canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);

        canvas.drawColor(Color.TRANSPARENT);

        for (VisionDetRet detRet : detRets) {
            Rect rect = new Rect(detRet.getLeft(), detRet.getTop(), detRet.getRight(), detRet.getBottom());
            canvas.drawRect(rect, mPaint);
        }

        mSurfaceHolder.unlockCanvasAndPost(canvas);

    }
}
