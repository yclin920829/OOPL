#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::UIUpdate() {
    LOG_TRACE("Start");



    if(IsBackFromGame){
        NowUI = std::make_shared<UISystem>();
        NowUI -> Initialize();
        root.AddChild(NowUI);
        IsBackFromGame = false;
    }

    glm::vec2 nowCursor = Util::Input::GetCursorPosition();




    if(Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)){//進入關卡(加條件)按下GameStart後
        if(NowUI -> CheckOnButton(nowCursor) == 1){
            NowUI -> DeleteButton();
            m_CurrentState = State::START;
        }
        if(NowUI -> CheckOnButton(nowCursor) == 2){
            m_CurrentState = State::END;
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {//如果被按下GameOver也要
        m_CurrentState = State::END;
    }

    root.Update();
}
