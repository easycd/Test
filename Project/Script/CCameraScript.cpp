#include "pch.h"
#include "CCameraScript.h"

#include <Engine\CTransform.h>
#include <Engine\CCamera.h>

CCameraScript::CCameraScript()
	: CScript((UINT)SCRIPT_TYPE::CAMERASCRIPT)
	, m_Target(nullptr)
	, m_fCamSpeed(5.f)
	, Offset(Vec3(0.f, 0.f, 0.f))
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::begin()
{
	if (m_Target != nullptr)
		Offset = GetOwner()->Transform()->GetRelativePos() - m_Target->Transform()->GetRelativePos();
}

void CCameraScript::tick()
{
		Camera3DMove();
}

void CCameraScript::Camera2DMove()
{
	// 키 입력에 따른 카메라 이동
	Vec3 vPos = Transform()->GetRelativePos();

	float fSpeed = m_fCamSpeed;
	if (KEY_PRESSED(KEY::LSHIFT))
		fSpeed *= 5.f;

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT * fSpeed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * fSpeed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * fSpeed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * fSpeed;
	}


	if (KEY_PRESSED(KEY::_1))
	{
		float fScale = Camera()->GetScale();
		fScale += DT * 1.f;
		Camera()->SetScale(fScale);
	}

	if (KEY_PRESSED(KEY::_2))
	{
		float fScale = Camera()->GetScale();
		fScale -= DT * 1.f;
		Camera()->SetScale(fScale);
	}

	Transform()->SetRelativePos(vPos);
}

void CCameraScript::Camera3DMove()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRot();

	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);

	float fSpeed = m_fCamSpeed;

	if (m_Target != nullptr)
	{
		Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();
		Vec3 CameraPos = GetOwner()->Transform()->GetRelativePos();

		CameraPos = TarGetPos + Offset;

		if (KEY_PRESSED(KEY::RBTN))
		{
			Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();
			vRot.y += DT * vMouseDir.x * 0.5f;
			vRot.x -= DT * vMouseDir.y * 0.5f;
		}

		Transform()->SetRelativePos(CameraPos);
		//Transform()->SetRelativePos(TarGetPos);
		//Transform()->SetRelativePos(vPos);
		Transform()->SetRelativeRot(vRot);
		//Vector3 dir = TarGetPos - CameraPos;

		//Vector3 MoveVector = Vec3(dir.x * fSpeed * DT, dir.y * fSpeed * DT, dir.z * fSpeed * DT);

		

		//if (KEY_PRESSED(KEY::LSHIFT))
		//	fSpeed *= 10.f;

		//if (KEY_PRESSED(KEY::W))
		//{
		//	//TarGetPos += DT * vFront * fSpeed;
		//	//vPos.z += DT * vFront.z * fSpeed;
		//	
		//}

		//if (KEY_PRESSED(KEY::S))
		//{
		//	//vPos.z -= DT * vFront.z * fSpeed;
		//}

		//if (KEY_PRESSED(KEY::A))
		//{
		//	//vPos.x -= DT * vRight.x * fSpeed;
		//}

		//if (KEY_PRESSED(KEY::D))
		//{
		//	//vPos.x += DT * vRight.x * fSpeed;
		//}

	}

}
