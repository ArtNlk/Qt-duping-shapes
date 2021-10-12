#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include <QCommandLineParser>

#include "duplicatingshapesmodel.h"
#include "duplicatingshape.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QCommandLineParser parser;

        parser.process(app);

        QLocale locale;
        if(parser.positionalArguments().size() > 0)
        {
            if(parser.positionalArguments().at(0) == "ru")
            {
                locale = QLocale::Russian;
            }else if(parser.positionalArguments().at(0) == "en")
            {
                locale = QLocale::English;
            }else
            {
                locale = QLocale::system();
            }
        }
        else
        {
            locale = QLocale::system();
        }

        qDebug() << "Loading locale: " << locale.language();

        const char* dirs[] = {
            "../translations",
            "/translations",
            0
        };

        QTranslator translator;
        bool translatorLoaded = false;
        for(const char* dir : dirs)
        {
            translatorLoaded = translator.load(locale,"Qt-csv-editor","_",dir);
            if(translatorLoaded) break;
        }
        if(translatorLoaded)
        {
            app.installTranslator(&translator);
        }

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/forms/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<DuplicatingShapesModel>("DupingShapes",1,0,"DupingShapesModel");
    qmlRegisterType<DuplicatingShape>("DupingShapes",1,0,"DupingShape");
    DuplicatingShape::setMaxVerts(25);
    DuplicatingShape::setDefaultLifetime(5000);
    engine.load(url);

    return app.exec();
}
