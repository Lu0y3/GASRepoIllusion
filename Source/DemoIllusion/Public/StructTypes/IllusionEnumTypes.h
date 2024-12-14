#pragma once

UENUM()
enum class EIllusionConfrimType : uint8
{
	//去确认是输入还是输出参数	
	Yes,
	No
};

UENUM()
enum class EIllusionValidType : uint8
{
	//去确认是有效还是无效参数	
	Valid,
	Invalid
};

UENUM()
enum class EIllusionSuccessType : uint8
{
	//去确认是Apply是否成功
	Successful,
	Failed
};
