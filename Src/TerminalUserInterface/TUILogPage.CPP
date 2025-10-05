#include "TerminalUserInterface/TUILogPage.HPP"

#include <ftxui/dom/table.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

TUILogPage::TUILogPage() {
    LogRenderer = ftxui::Renderer([this] { return this->Rendering(); });
}

ftxui::Element TUILogPage::Rendering() {
    auto Logs = LogCollector::GetInstance().GetLogs();

    std::vector<std::vector<std::string>> TableData;
    TableData.push_back({boost::locale::translate("Time"), boost::locale::translate("Type"), boost::locale::translate("Message")});
    for (const auto& Entry : Logs) {
        TableData.push_back({Entry.TimeStamp, Entry.Level, Entry.Message});
    }

    auto Table = ftxui::Table(TableData);

    Table.SelectColumn(0).DecorateCells(ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 20));
    Table.SelectColumn(1).DecorateCells(ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 7));
    Table.SelectColumn(2).DecorateCells(ftxui::flex);

    Table.SelectAll().Border(ftxui::LIGHT);
    Table.SelectRow(0).Decorate(ftxui::bold);
    Table.SelectRow(0).SeparatorVertical(ftxui::LIGHT);
    Table.SelectRow(0).Border(ftxui::DOUBLE);
    Table.SelectColumn(0).DecorateCells(ftxui::color(ftxui::Color::GrayDark));
    Table.SelectColumn(1).DecorateCells(ftxui::bold);

    for (int i = 0; i < Logs.size(); ++i) {
        ftxui::Decorator LevelDecorator;
        if (Logs[i].Level == "INFO") {
            LevelDecorator = ftxui::color(ftxui::Color::Green);
        } else if (Logs[i].Level == "WARN") {
            LevelDecorator = ftxui::color(ftxui::Color::Yellow);
        } else if (Logs[i].Level == "ERROR") {
            LevelDecorator = ftxui::color(ftxui::Color::Red);
        }
        Table.SelectRow(i + 1).DecorateCells(LevelDecorator);
    }

    auto TableElements = Table.Render();

    return TableElements | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex;
}

ftxui::Component TUILogPage::GetComponent() {
    return LogRenderer;
}

std::string TUILogPage::PageName() {
    return boost::locale::translate("Log Manage");
}