#ifndef __GAUSSIANBLUROBJECT_H__
#define __GAUSSIANBLUROBJECT_H__

class GaussianBlurDelegate;

class GaussianBlurObject
	: public ExtLayoutObjMethodsImpl
{
public:
public:

	GaussianBlurObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~GaussianBlurObject(void);

public:

	enum Type {
		UnDefined = 0,
//		OneDimention = 1, 
//		OneDimentionSSE = 2,
		OneDimentionMMX = 3, 
//		TwoDimention = 4, 
//		DirecheIIR = 5, 
		DirecheIIRSSE = 6, 
//		DirecheIIRSSEIntrinsics = 7, 
		Default = 8
	};

	// ExtLayoutObjMethodsImpl virtual funtions

	// �ö����Ǽ������еģ�������Ҫ���LayerObject+clipsensʹ��
	virtual void OnPaint(XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect, const RECT* lpSrcClipRect, unsigned char alpha);

	void SetSigma(double sigma);
	double GetSigma()const {return m_sigma;}

	void SetRadius(int radius) {m_radius = radius;}
	int GetRadius()const {return m_radius;}

	void SetType(const char *type) ;
	const char* GetType()const;

private:
	double m_sigma;
	int m_radius;
	Type m_type;
};

#endif // __GAUSSIANBLUROBJECT_H__