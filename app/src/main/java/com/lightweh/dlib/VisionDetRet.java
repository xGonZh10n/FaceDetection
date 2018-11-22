/*
 *  Copyright (C) 2015 TzuTaLin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.lightweh.dlib;


/**
 * Created by Tzutalin on 2015/10/20.
 * Modified by Lightweh on Nov 21, 2018
 */


public final class VisionDetRet {

    private int mLeft;
    private int mTop;
    private int mRight;
    private int mBottom;

    VisionDetRet() {}

    /**
     * @param l          The X coordinate of the left side of the result
     * @param t          The Y coordinate of the top of the result
     * @param r          The X coordinate of the right side of the result
     * @param b          The Y coordinate of the bottom of the result
     */
    public VisionDetRet(int l, int t, int r, int b) {
        mLeft = l;
        mTop = t;
        mRight = r;
        mBottom = b;
    }

    /**
     * @return The X coordinate of the left side of the result
     */
    public int getLeft() {
        return mLeft;
    }

    /**
     * @return The Y coordinate of the top of the result
     */
    public int getTop() {
        return mTop;
    }

    /**
     * @return The X coordinate of the right side of the result
     */
    public int getRight() {
        return mRight;
    }

    /**
     * @return The Y coordinate of the bottom of the result
     */
    public int getBottom() {
        return mBottom;
    }
}
