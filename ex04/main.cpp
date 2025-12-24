#include "DateDecorator.hpp"
#include "HeaderDecorator.hpp"
#include "LoggerFile.hpp"
#include "LoggerStream.hpp"

#include <vector>

void write(const std::vector<ILogger *> &loggers, const std::string &message);

int main()
{
    LoggerStream logger_stdout1(std::cout);
    HeaderDecorator logger_stdout2("[STDOUT]", logger_stdout1);
    DateDecorator logger_stdout3(logger_stdout2);

    LoggerFile logger_file1("file_log.txt");
    HeaderDecorator logger_file2("[FILE]", logger_file1);
    DateDecorator logger_file3(logger_file2);

    std::vector<ILogger *> loggers;
    loggers.push_back(&logger_stdout3);
    loggers.push_back(&logger_file3);

    std::vector<std::string> messages;
    messages.push_back("こんにちは、こちらはハッピーログデコレータです\n");
    messages.push_back("デコレータパターンというものを使うことで、\n");
    messages.push_back("各ログごとにどんなヘッダーをつけるか、\n");
    messages.push_back("日付を付与するかを決めれます。\n");
    messages.push_back("\n");
    messages.push_back("これの何が良いのでしょうか。\n");
    messages.push_back("\n");
    messages.push_back("それは、元のLoggerクラスをいじらずに\n");
    messages.push_back("ログに付与する情報を決めることができる点です。\n");
    messages.push_back("そのクラスを使う側（今回だとmain.cpp）\n");
    messages.push_back("が自由に、情報を決めることができます。\n");
    messages.push_back("\n");
    messages.push_back("２個のヘッダーを追加したいときは？３つは？４つは？という場合でも\n");
    messages.push_back("Loggerクラスをいじる必要がありません。\n");
    messages.push_back("\n");
    messages.push_back("いじらないことで、Loggerクラスのテストを行う回数を減らすことができ\n");
    messages.push_back("問題の特定や、機能更新を迅速に行うことができます。\n");

    std::vector<std::string>::iterator it = messages.begin();
    std::vector<std::string>::iterator ite = messages.end();
    while (it != ite)
    {
        write(loggers, *it);
        it++;
    }
    return (0);
}

void write(const std::vector<ILogger *> &loggers, const std::string &message)
{
    std::vector<ILogger *>::const_iterator it = loggers.begin();
    std::vector<ILogger *>::const_iterator ite = loggers.end();

    while (it != ite)
    {
        (*it)->write(message);
        it++;
    }
}
