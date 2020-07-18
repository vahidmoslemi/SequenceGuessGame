#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <memory>

#include "gamecore.h"
#include "strategyfunctions.h"
#include "uihandler.h"
#include "eventlistenerinterface.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    auto engine = std::make_unique<QQmlApplicationEngine>();

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine->rootObjects().isEmpty())
        return -1;

    const int ksequence_length = 3;


    auto game_core = std::make_shared<GameCore>(
                             StrategyFunctions::GetSequenceGenerator(),
                             ksequence_length,
                             StrategyFunctions::GetResultProcessor()
                         );
    game_core->StartNewGame();

    auto ui_handler = std::make_shared<UIHandler>(engine);

    ui_handler->registerEventListener(game_core);
    game_core->registerEventListener(ui_handler);

    //---------------------------------------------------------------------------

    return app.exec();
//    return 0;
}
