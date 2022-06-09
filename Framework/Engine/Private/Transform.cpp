#include "Transform.h"

CTransform::CTransform(const CTransform& Prototype)
{
	*this = Prototype;

}

CTransform* CTransform::Create()
{
	return nullptr;
}

CComponent* CTransform::Clone(void* Arg)
{
	return nullptr;
}
