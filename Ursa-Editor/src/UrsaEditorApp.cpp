#include <Ursa.h>
#include "Ursa/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Ursa {
	class UrsaEditor : public Application {
	public:
		UrsaEditor() : Application("Ursa Editior")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~UrsaEditor() {

		}
	};

	Application* CreateApplication() {
		return new UrsaEditor();
	}
}