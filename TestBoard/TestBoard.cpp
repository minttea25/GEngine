// TestBoard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "Test.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2Int.h"
#include "Vector2.h"
#include "GTime.h"

#include "EditorResourceManager.h"

using namespace GEngine::Types;
using namespace GEngine;

int main()
{
    std::cout << "Hello World!\n";

    GEngine::Editor::EditorResourceManager::Init();
    GEngine::Editor::EditorResourceManager::TestImport(L"Folder");

    return 0;

    {
        std::cout << "Add(1, 2): " << Test::Add(1, 2) << '\n';
        std::cout << "Sub(5, 3): " << Test::Sub(5, 3) << '\n';

        {
            Vector4 v4(1, 1, 1, 1);
            std::cout << Vector4::Magnitude(v4) << '\n';
            auto v = Vector4::Normalize(v4);
            std::cout << v.x << ',' << v.y << ',' << v.z << ',' << v.w << '\n';
        }

        {
            Vector3 v3(1, 1, 1);
            std::cout << Vector3::Magnitude(v3) << '\n';
            auto v = Vector3::Normalize(v3);
            std::cout << v.x << ',' << v.y << ',' << v.z << '\n';
        }

        {
            Vector2Int v2int(1, 1);
            std::cout << v2int.magnitude() << '\n';
            float dist = Vector2Int::Distance(v2int, Vector2Int(2, 2));
            std::cout << dist << '\n';
        }

        {
            Vector2 v(1, 1);
            std::cout << v.magnitude() << '\n';
            auto dist = Vector2::Distance(v, Vector2(4, 5));
            std::cout << dist << '\n';
        }

        {
            using namespace std::chrono_literals;

            Time::Init();

            while (true)
            {
                Time::Update();

                std::this_thread::sleep_for(100ms);
                std::cout << Time::deltaTime() << '\n';
            }
        }
    }


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
