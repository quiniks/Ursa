#include "ursapch.h"
#include "SceneSerializer.h"
#include "Entity.h"
#include "Components.h"

#include <yaml-cpp/yaml.h>
#include <fstream>

//TEMP
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace YAML {
	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs) {
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs) {
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Ursa {
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity) {
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << "12837192831273";

		if (entity.HasComponent<TagComponent>()) {
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap;
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;
			out << YAML::EndMap;
		}

		if (entity.HasComponent<TransformComponent>()) {
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap;
			auto& tc = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;
			out << YAML::EndMap;
		}

		if (entity.HasComponent<CameraComponent>()) {
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap;
			auto& cc = entity.GetComponent<CameraComponent>();
			auto& camera = cc.Camera;
			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap;
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
			out << YAML::EndMap;

			out << YAML::Key << "Primary" << YAML::Value << cc.Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cc.FixedAspectRatio;
			out << YAML::EndMap;
		}

		if (entity.HasComponent<SpriteComponent>()) {
			out << YAML::Key << "SpriteComponent";
			out << YAML::BeginMap;
			auto& sc = entity.GetComponent<SpriteComponent>();
			out << YAML::Key << "Color" << YAML::Value << sc.Color;
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize(const std::string& filePath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID) {
			Entity entity = { entityID, m_Scene.get() };
			if (!entity)
				return;
			SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filePath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filePath)
	{
		URSA_CORE_ASSERT(false, "Scene runtime serializing not implemented");
	}

	bool SceneSerializer::Deserialize(const std::string& filePath)
	{
		std::ifstream fs(filePath);
		std::stringstream ss;
		ss << fs.rdbuf();

		YAML::Node data = YAML::Load(ss.str());
		if (!data["Scene"])
			return false;
		std::string sceneName = data["Scene"].as<std::string>();
		URSA_CORE_TRACE("Deserializing scene '{0}'", sceneName);

		auto entitiesNode = data["Entities"];
		if (entitiesNode) {
			for (auto entityItr : entitiesNode) {
				uint64_t uuid = entityItr["Entity"].as<uint64_t>();

				std::string name;
				auto tagComponentNode = entityItr["TagComponent"];
				if (tagComponentNode)
					name = tagComponentNode["Tag"].as<std::string>();
				URSA_CORE_TRACE("Deserialized entity '{0}' '{1}'", uuid, name);
			
				Entity deserializedEntity = m_Scene->CreateEntity(name);

				auto transformComponentNode = entityItr["TransformComponent"];
				if (transformComponentNode) {
					auto& tc = deserializedEntity.GetComponent<TransformComponent>();
					tc.Translation = transformComponentNode["Translation"].as<glm::vec3>();
					tc.Rotation = transformComponentNode["Rotation"].as<glm::vec3>();
					tc.Scale = transformComponentNode["Scale"].as<glm::vec3>();
				}

				auto cameraComponentNode = entityItr["CameraComponent"];
				if (cameraComponentNode) {
					auto& cc = deserializedEntity.AddComponent<CameraComponent>();
					auto& cameraPropNode = cameraComponentNode["Camera"];

					cc.Camera.SetProjectionType((SceneCamera::ProjectionType)cameraPropNode["ProjectionType"].as<int>());

					cc.Camera.SetPerspectiveVerticalFOV(cameraPropNode["PerspectiveFOV"].as<float>());
					cc.Camera.SetPerspectiveNearClip(cameraPropNode["PerspectiveNear"].as<float>());
					cc.Camera.SetPerspectiveFarClip(cameraPropNode["PerspectiveFar"].as<float>());

					cc.Camera.SetOrthographicSize(cameraPropNode["OrthographicSize"].as<float>());
					cc.Camera.SetOrthographicNearClip(cameraPropNode["OrthographicNear"].as<float>());
					cc.Camera.SetOrthographicFarClip(cameraPropNode["OrthographicFar"].as<float>());

					cc.Primary = cameraComponentNode["Primary"].as<bool>();
					cc.FixedAspectRatio = cameraComponentNode["FixedAspectRatio"].as<bool>();
				}

				auto spriteComponentNode = entityItr["SpriteComponent"];
				if (spriteComponentNode) {
					auto& sc = deserializedEntity.AddComponent<SpriteComponent>();
					sc.Color = spriteComponentNode["Color"].as<glm::vec4>();
				}
			}
		}
		return true;
	}

	bool SceneSerializer::DeserializeRuntime(const std::string& filePath)
	{
		URSA_CORE_ASSERT(false, "Scene runtime deserializing not implemented");
		return false;
	}
}