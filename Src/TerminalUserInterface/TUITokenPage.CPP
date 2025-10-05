#include "TerminalUserInterface/TUITokenPage.HPP"

#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>

TUITokenPage::TUITokenPage() {
    MainContainer_ = ftxui::Renderer([this] { return this->Rendering(); });
}

ftxui::Element TUITokenPage::Rendering() {
    std::vector<std::vector<std::string>> data = {
        {"ID", "Product", "Quantity", "Price"},
        {"1", "Laptop", "5", "$1200"},
        {"2", "Mouse", "30", "$25"},
        {"3", "Keyboard", "15", "$75"},
    };

    // 2. 创建 Table 对象
    auto table = ftxui::Table(data);

    // 3. 渲染成 Element
    ftxui::Element table_element = table.Render();
    return table_element;
}

std::string TUITokenPage::PageName() {
    return boost::locale::translate("Token Manage");
}

ftxui::Component TUITokenPage::GetComponent() {
    return ftxui::Renderer([this] { return this->Rendering(); });
}