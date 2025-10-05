#include "TerminalUserInterface/TUIPluginPage.HPP"

#include <ftxui/dom/table.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/component.hpp>

TUIPluginPage::TUIPluginPage() {
    PluginManage_ = std::make_unique<PluginManage>();
    PluginManage_->LoadingPlugins("Plugins");

    MainComponents_ = ftxui::Renderer([this] { return this->Rendering(); });
}

ftxui::Element TUIPluginPage::Rendering() {
    const auto& Plugins = PluginManage_->GetLoadedPlugins();

    std::vector<std::vector<std::string>> TableData;
    TableData.push_back({
        boost::locale::translate("Plugin Name"),
        boost::locale::translate("Version"),
        boost::locale::translate("Author"),
        boost::locale::translate("Description")
    });

    if (Plugins.empty()) {
        TableData.push_back({"No plugins loaded.", "", "", ""});
    } else {
        for (const auto& PluginInfo : Plugins) {
            TableData.push_back({
                PluginInfo.Instance->Name(),
                PluginInfo.Instance->Version(),
                PluginInfo.Instance->Author(),
                PluginInfo.Instance->Description()
            });
        }
    }

    auto Table = ftxui::Table(TableData);

    Table.SelectAll().Border(ftxui::LIGHT);
    Table.SelectRow(0).Decorate(ftxui::bold);
    Table.SelectRow(0).DecorateCells(ftxui::center);
    Table.SelectRow(0).SeparatorVertical(ftxui::LIGHT);
    Table.SelectRow(0).Border(ftxui::DOUBLE);

    Table.SelectColumn(0).DecorateCells(ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 20));
    Table.SelectColumn(1).DecorateCells(ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 10));
    Table.SelectColumn(2).DecorateCells(ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 15));
    Table.SelectColumn(3).DecorateCells(ftxui::flex);

    for (size_t i = 0; i < Plugins.size(); ++i) {
        if ((i + 1) % 2 == 0) {
            Table.SelectRow(i + 1).DecorateCells(ftxui::bgcolor(ftxui::Color::GrayDark));
        }
    }

    return Table.Render() | ftxui::vscroll_indicator | ftxui::frame | ftxui::flex;
}

std::string TUIPluginPage::PageName() {
    return boost::locale::translate("Plugins Manage");
}

ftxui::Component TUIPluginPage::GetComponent() {
    return ftxui::CatchEvent(MainComponents_, [](ftxui::Event) { return false; });
}