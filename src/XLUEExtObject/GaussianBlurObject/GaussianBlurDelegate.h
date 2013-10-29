#ifndef _GAUSSIANBLURDELEGATE_H_
#define _GAUSSIANBLURDELEGATE_H_

void DericheIIRRenderSSEIntrinsics(XL_BITMAP_HANDLE hBitmap, double m_sigma);
void DericheIIRRenderSSE(XL_BITMAP_HANDLE hBitmap, double m_sigma);
void DericheIIRRender(XL_BITMAP_HANDLE hBitmap, double m_sigma);
void TwoDimentionRender(XL_BITMAP_HANDLE hBitmap, double m_sigma, int m_radius);
void OneDimentionRender(XL_BITMAP_HANDLE hBitmap, double m_sigma, int m_radius);
void OneDimentionRenderSSE(XL_BITMAP_HANDLE hBitmap, double m_sigma, __int32 m_radius);
void OneDimentionRenderMMX(XL_BITMAP_HANDLE hBitmpa, double m_sigma, __int32 m_radius);

#endif //_GAUSSIANBLURDELEGATE_H_