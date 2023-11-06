#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "MonoBehaviour.h"

shared_ptr<Component> component = make_shared<Transform>();

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
	AddComponent(make_shared<Transform>());//����Ƽ�� ������Ʈó�� �⺻������ Transform�� ��� �ְԲ�
}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Awake();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Start();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Update();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->LateUpdate();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LateUpdate();
	}
}

shared_ptr<Transform> GameObject::GetTransform()
{
	uint8 index = static_cast<uint8>(COMPONENT_TYPE::TRANSFORM);
	return static_pointer_cast<Transform>(_components[index]);
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	// SetGameObject�� shared_ptr�� �ް� �ִ�. 
	// �̴� �Ϲ����� this �����ͷ� �ѱ� �� ����.
	// ������ 'enable_shared_from_this<>'�� ��� �޾� 'shared_from_this'�� ����Ͽ� �Ѱ��ش�.
	// shared_from_this�� �ڽ��� weak_ptr�� ����� �Ѱܴ���.
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		// ������ Ŀ���� ��ũ��Ʈ
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}
