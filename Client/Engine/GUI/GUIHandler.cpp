#include "GUIHandler.hpp"
#include "../../Constants.hpp"

void GUIHandler::init(){

	m_guiRenderer.init();
	m_guiShader.init();
	m_fontShader.init();

	m_matrix = glm::ortho(0.0f, (float)Constants::getScreenWidth(), 0.0f, (float)Constants::getScreenHeight());

}

void GUIHandler::createWorkspaces(unsigned int numWorkspaces){
	for(unsigned int i = 0; i < numWorkspaces; i++) workspaces.emplace_back();
}

void GUIHandler::renderWorkspace(unsigned int numWorkspace){
	workspaces.at(numWorkspace).render(m_guiRenderer, m_guiShader, m_fontShader, fonts, m_matrix);
}

void GUIHandler::updateWorkspace(unsigned int numWorkspace){
	workspaces.at(numWorkspace).update();
}

void GUIHandler::updateAll(){
	for(auto& i : workspaces){
		i.update();
	}
}

void GUIHandler::renderAll(){
	for(auto& i : workspaces){
		i.render(m_guiRenderer, m_guiShader, m_fontShader, fonts, m_matrix);
	}
}

void GUIHandler::destroy(){

	//Deleting fonts
	for(auto& i : fonts){
		i.destroy();
	}

	//Deleting text meshes inside of workspaces
	for(auto& i : workspaces){
		for(auto& j : i.textMeshes){
			j.destroy();
		}
	}

	m_fontShader.destroy();
	m_guiShader.destroy();
	m_guiRenderer.destroy();
}
