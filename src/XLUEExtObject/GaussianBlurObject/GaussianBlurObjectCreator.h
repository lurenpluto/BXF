#ifndef __GAUSSIANBLUROBJECTCREATOR_H__
#define __GAUSSIANBLUROBJECTCREATOR_H__

#include "./GaussianBlurObject.h"

class GaussianBlurObjectCreator
	: public ExtObjCreatorImpl<GaussianBlurObject>
{
public:
	GaussianBlurObjectCreator(void);
	virtual ~GaussianBlurObjectCreator(void);

private:

	virtual GaussianBlurObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(GaussianBlurObject* lpObj);
};

#endif // __GAUSSIANBLUROBJECTCREATOR_H__