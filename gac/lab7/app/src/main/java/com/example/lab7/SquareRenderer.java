package com.example.lab7;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;

import android.content.Context;
import android.opengl.GLSurfaceView;
import java.lang.Math;

public class SquareRenderer implements GLSurfaceView.Renderer {
    private Square mSquare;
    private Square mSquare2;
    private float mTransY;
    private Context mContext;

    public SquareRenderer(Context context) {
        this.mContext = context;

        float squareColorsYMCA[] = {
                1.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 1.0f
        };

        float squareColorsRGBA[] = {
                1.0f, 0.0f, 0.0f, 1.0f,
                0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f
        };

        mSquare = new Square(squareColorsYMCA, context);
        mSquare2 = new Square(squareColorsRGBA, context);
    }

    public void onDrawFrame(GL10 gl) {
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        gl.glMatrixMode(GL10.GL_MODELVIEW);
        gl.glLoadIdentity();

        gl.glTranslatef(0.0f, (float)Math.sin(mTransY), -3.0f);
        mSquare.draw(gl);

        gl.glLoadIdentity();
        gl.glTranslatef((float)(Math.sin(mTransY)/2.0f), 0.0f, -2.9f);
        mSquare2.draw(gl);

        mTransY += .075f;
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        gl.glViewport(0, 0, width, height);
        gl.glMatrixMode(GL10.GL_PROJECTION);
        gl.glLoadIdentity();
        float ratio = (float) width / height;
        gl.glFrustumf(-ratio, ratio, -1, 1, 1, 10);
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        gl.glDisable(GL10.GL_DITHER);
        gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT, GL10.GL_FASTEST);
        gl.glClearColor(0, 0, 0, 1);
        gl.glEnable(GL10.GL_CULL_FACE);
        gl.glShadeModel(GL10.GL_SMOOTH);
        gl.glEnable(GL10.GL_DEPTH_TEST);
        gl.glEnable(GL10.GL_TEXTURE_2D); // ✅ Make sure texture rendering is enabled

        // ✅ Load textures ONCE
        mSquare.setTextures(gl, mContext, R.drawable.a, R.drawable.cooked);
        mSquare2.setTextures(gl, mContext, R.drawable.a, R.drawable.cooked);
    }
}

