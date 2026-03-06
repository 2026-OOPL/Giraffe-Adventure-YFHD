#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <memory>

void MoveGraffiePosition(std::shared_ptr<Character> m_Giraffe) {

    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        m_Giraffe->MoveByOffset({-1, 0});
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        m_Giraffe->MoveByOffset({1, 0});
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        m_Giraffe->MoveByOffset({0, 1});
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        m_Giraffe->MoveByOffset({0, -1});
    }
}

void CheckChestCollision(std::shared_ptr<Character> m_Giraffe, std::shared_ptr<Character> m_Chest) {
    if (m_Chest->IfCollides(m_Giraffe)) {
        m_Chest->SetVisible(false);
    }
}

void HandleDoorOpen(std::shared_ptr<Character> m_Giraffe, std::vector<std::shared_ptr<Character>> m_Doors) {
    for (auto& i : m_Doors) {
        if (m_Giraffe->IfCollides(i)) {
            i->SetImage(GA_RESOURCE_DIR"/Image/Character/door_open.png");
        } else {
            i->SetImage(GA_RESOURCE_DIR"/Image/Character/door_close.png");
        }
    }
}

void HandleBeeAnimation() {
    
}

void App::Update() {

    // TODO: Add your own logics to finish the tasks in README.md

    /*
     *  Do not touch the code below as they serve the purpose for validating the tasks,
     *  rendering the frame, and exiting the game.
    */

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
            ValidTask();
        }
    }
    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);
    
    MoveGraffiePosition(m_Giraffe);
    CheckChestCollision(m_Giraffe, m_Chest);
    HandleDoorOpen(m_Giraffe, m_Doors);
    
    switch (m_Phase) {
        case Phase::BEE_ANIMATION:
            m_Bee->SetVisible(true);
            m_Bee->SetLooping(true);
            break;

        case Phase::COUNTDOWN:
            m_Ball->SetVisible(true);
        default:
            break;
    }    

    m_Root.Update();
}

