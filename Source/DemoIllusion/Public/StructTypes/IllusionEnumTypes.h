#pragma once

UENUM()
enum class EIllusionConfrimType : uint8
{
	//ȥȷ�������뻹���������	
	Yes,
	No
};

UENUM()
enum class EIllusionValidType : uint8
{
	//ȥȷ������Ч������Ч����	
	Valid,
	Invalid
};

UENUM()
enum class EIllusionSuccessType : uint8
{
	//ȥȷ����Apply�Ƿ�ɹ�
	Successful,
	Failed
};
