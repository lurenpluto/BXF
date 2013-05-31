/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   RippleItem
*   Author      :   李亚星
*   Create      :   2013-5-28
*   LastChange  :   2013-5-31
*   History     :	
*
*   Description :   模拟一个水滴落到水面的效果，可叠加，核心算法参考下面的链接地址：
*					http://freespace.virgin.net/hugo.elias/graphics/x_water.htm
*					水波的起始高度，起始半径和衰减因子决定了水波的扩散范围，使用RippleItemGenerator
*					可以生成合适width的水波，如果width过小，水波边缘会出现反射
*
********************************************************************/ 
#ifndef __RIPPLEITEM_H__
#define __RIPPLEITEM_H__

class RippleItem
{
public:
	RippleItem(size_t width, short radius, short height, char dampingRatio, bool fineMode);
	~RippleItem(void);

	void Draw(XL_BITMAP_HANDLE hBitmap, const RECT* lpDestRect, const RECT* lpSrcRect);

	size_t GetWidth() const
	{
		return m_width;
	}

	bool UpdateFrame();

private:

	// 初始化圆形水波区域
	void Init();

	// 演算水波数据
	void Update(size_t& leftPoints);

	void UpdateInFineMode(const short *lpOldFrameBuffer, short* lpNewFrameBuffer, size_t& leftPoints);
	void UpdateInNormalMode(const short *lpOldFrameBuffer, short* lpNewFrameBuffer, size_t& leftPoints);

private:

	// 水波的扩散区间，为正方形区域
	size_t m_width;

	// 水波起始作用域半径，以扩散区间为中心，一般都在10个像素以内
	short m_radius;

	// 水波起始高度，以100为标准值
	short m_height;

	// 衰减系数，为了便于计算使用二次幂衰减，比如1表示每次衰减量为先前一半，2表示每次衰减量为先前1/4
	char m_dampingRatio;

	// 水波模式，精细模式采用3*3矩阵卷积，普通模式只采用上下左右四点卷积
	bool m_fineMode;

	// 水波的帧缓冲，一个周期有三帧，所以需要两个缓冲区
	// 以后为了更精细计算，可以引入五帧周期
	short *m_lpFrameBuffer1, *m_lpFrameBuffer2;

	// 当前帧的缓冲区，两个帧缓冲轮流切换
	short *m_lpCurrentFrame;

	short m_fadeHeight;
};

// 随机水滴生成器
class RippleItemGenerator
{
public:

	static RippleItem* Generate(short radius, short height, char dampingRatio, bool fineMode);
};

#endif //__RIPPLEITEM_H__