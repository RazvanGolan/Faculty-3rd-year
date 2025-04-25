package com.example.lab7;

import static android.opengl.ETC1Util.createTexture;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLUtils;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;

public class Square {
    private FloatBuffer mFVertexBuffer;
    private ByteBuffer mColorBuffer;
    private ByteBuffer mIndexBuffer;
    private int mTexture0;
    private int mTexture1;
    private int[] textures = new int[1];
    public FloatBuffer mTextureBuffer;
    private Context context;

    public float[] textureCoords =
            {
                    0.0f , 2.0f,
                    2.0f , 2.0f,
                    0.0f , 0.0f,
                    2.0f , 0.0f
            };

    public Square(float[] colors, Context context) {
        float vertices[] =
                {
                        -1.0f, -1.0f,
                        1.0f, -1.0f,
                        -1.0f, 1.0f,
                        1.0f, 1.0f
                };
        byte maxColor=(byte)255;
        byte indices[] =
                {
                        0, 3, 1,
                        0, 2, 3
                };

        byte[] colorsByte = new byte[colors.length];

        for (int i = 0; i < colors.length; i++) {
            colorsByte[i] = (byte)(colors[i] * maxColor);
        }

        ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length * 4);
        vbb.order(ByteOrder.nativeOrder());
        mFVertexBuffer = vbb.asFloatBuffer();
        mFVertexBuffer.put(vertices);
        mFVertexBuffer.position(0);
        mColorBuffer = ByteBuffer.allocateDirect(colors.length);
        mColorBuffer.put(colorsByte);
        mColorBuffer.position(0);
        mIndexBuffer = ByteBuffer.allocateDirect(indices.length);
        mIndexBuffer.put(indices);
        mIndexBuffer.position(0);

        ByteBuffer tbb = ByteBuffer.allocateDirect(textureCoords.length * 4);
        tbb.order(ByteOrder.nativeOrder());
        mTextureBuffer = tbb.asFloatBuffer();
        mTextureBuffer.put(textureCoords);
        mTextureBuffer.position(0);

        this.context = context;
    }

    public void draw(GL10 gl)
    {
        setTextures(gl, context, R.drawable.a, R.drawable.cooked);
        gl.glEnable(GL10.GL_TEXTURE_2D);

        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
        gl.glEnableClientState(GL10.GL_COLOR_ARRAY);

        gl.glFrontFace(GL11.GL_CW);
        gl.glVertexPointer(2, GL10.GL_FLOAT, 0, mFVertexBuffer);
        gl.glColorPointer(4, GL10.GL_UNSIGNED_BYTE, 0, mColorBuffer);

        gl.glClientActiveTexture(GL10.GL_TEXTURE0);
        gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
        gl.glBindTexture(GL10.GL_TEXTURE_2D, mTexture0);
        gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, mTextureBuffer);

        gl.glClientActiveTexture(GL10.GL_TEXTURE1);
        gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
        gl.glBindTexture(GL10.GL_TEXTURE_2D, mTexture1);
        gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, mTextureBuffer);

        gl.glTexEnvf(GL10.GL_TEXTURE_ENV, GL10.GL_TEXTURE_ENV_MODE, GL10.GL_MODULATE);

        gl.glDrawElements(GL10.GL_TRIANGLES, 6, GL10.GL_UNSIGNED_BYTE, mIndexBuffer);
    }

    public void setTextures(GL10 gl, Context context, int resourceID0, int resourceID1)
    {
        mTexture0 = createTexture(gl,context,resourceID0);
        mTexture1 = createTexture(gl,context,resourceID1);
    }

    public int createTexture(GL10 gl, Context contextRegf, int resource)
    {
        Bitmap image = BitmapFactory.decodeResource(contextRegf.getResources(), resource);
        gl.glGenTextures(1, textures, 0);
        gl.glBindTexture(GL10.GL_TEXTURE_2D, textures[0]);
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, image, 0);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_LINEAR);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);
        image.recycle();

        return textures[0];
    }

    public void multiTexture(GL10 gl, int tex0, int tex1)
    {
        float combineParameter = GL10.GL_MODULATE;
        gl.glActiveTexture(GL10.GL_TEXTURE0);
        gl.glBindTexture(GL10.GL_TEXTURE_2D, tex0);
        gl.glActiveTexture(GL10.GL_TEXTURE1);
        gl.glBindTexture(GL10.GL_TEXTURE_2D, tex1);
        gl.glTexEnvf(GL10.GL_TEXTURE_ENV, GL10.GL_TEXTURE_ENV_MODE, combineParameter);
    }
}
