#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <random>

#include "gamecore.h"
#include "strategyfunctions.h"
#include "uihandler.h"
#include "eventlistenerinterface.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine* engine =  new QQmlApplicationEngine();
    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine->rootObjects().isEmpty())
        return -1;

    const int ksequence_length = 3;


    GameCore* game_core (new GameCore(
                             StrategyFunctions::GetSequenceGenerator(),
                             ksequence_length,
                             StrategyFunctions::GetResultProcessor()
                             )
                         );
    game_core->StartNewGame();

    UIHandler* ui_handler(new UIHandler(engine));

    ui_handler->RegisterEventListener(dynamic_cast<EventListenerInterface*>(game_core));
    game_core->RegisterEventListener(dynamic_cast<EventListenerInterface*>(ui_handler));

    //---------------------------------------------------------------------------

    return app.exec();
//    return 0;
}
