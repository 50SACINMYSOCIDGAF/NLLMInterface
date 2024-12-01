// main.cpp
#include <QApplication>
#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QSpinBox>
#include <QTabWidget>
#include <QScrollArea>
#include <QFrame>
#include <QStyle>
#include <QString>

class LLMInterface : public QMainWindow {
public:
    LLMInterface(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("LLM Interface");
        setMinimumSize(1000, 600);
        setupUI();
        setStyleSheet(R"(
            QMainWindow {
                background-color: #1e1e1e;
                color: #ffffff;
            }
            QLabel, QComboBox, QPushButton, QSpinBox {
                color: #ffffff;
                background-color: #2d2d2d;
                border: 1px solid #3d3d3d;
                border-radius: 4px;
                padding: 5px;
            }
            QTextEdit {
                background-color: #2d2d2d;
                color: #ffffff;
                border: 1px solid #3d3d3d;
                border-radius: 4px;
            }
            QPushButton:hover {
                background-color: #3d3d3d;
            }
            QListWidget {
                background-color: #2d2d2d;
                color: #ffffff;
                border: 1px solid #3d3d3d;
                border-radius: 4px;
            }
            QTabWidget::pane {
                border: 1px solid #3d3d3d;
                background-color: #2d2d2d;
            }
            QTabBar::tab {
                background-color: #2d2d2d;
                color: #ffffff;
                padding: 8px 20px;
                border: 1px solid #3d3d3d;
            }
            QTabBar::tab:selected {
                background-color: #3d3d3d;
            }
        )");
    }

private:
    void setupUI() {
        // Main central widget
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        // Main layout
        QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
        
        // Left sidebar for chat list
        QWidget *leftSidebar = createLeftSidebar();
        mainLayout->addWidget(leftSidebar, 1);
        
        // Chat area
        QWidget *chatArea = createChatArea();
        mainLayout->addWidget(chatArea, 3);
        
        // Right sidebar for settings
        QWidget *rightSidebar = createRightSidebar();
        mainLayout->addWidget(rightSidebar, 1);
    }
    
    QWidget* createLeftSidebar() {
        QWidget *sidebar = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(sidebar);
        
        // New chat button
        QPushButton *newChatBtn = new QPushButton("New Chat");
        layout->addWidget(newChatBtn);
        
        // Chat list
        QListWidget *chatList = new QListWidget();
        chatList->addItem("Chat 1");
        chatList->addItem("Chat 2");
        chatList->addItem("Chat 3");
        layout->addWidget(chatList);
        
        return sidebar;
    }
    
    QWidget* createChatArea() {
        QWidget *chatWidget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(chatWidget);
        
        // Model selection
        QHBoxLayout *modelLayout = new QHBoxLayout();
        QLabel *modelLabel = new QLabel("Current Model:");
        QComboBox *modelSelect = new QComboBox();
        modelSelect->addItems({"GPT-4", "Local LLaMA", "Local Mistral", "Claude"});
        modelLayout->addWidget(modelLabel);
        modelLayout->addWidget(modelSelect);
        modelLayout->addStretch();
        layout->addLayout(modelLayout);
        
        // Chat history
        QTextEdit *chatHistory = new QTextEdit();
        chatHistory->setReadOnly(true);
        layout->addWidget(chatHistory);
        
        // Input area
        QTextEdit *inputArea = new QTextEdit();
        inputArea->setMaximumHeight(100);
        inputArea->setPlaceholderText("Type your message here...");
        layout->addWidget(inputArea);
        
        // Send button
        QPushButton *sendButton = new QPushButton("Send");
        layout->addWidget(sendButton);
        
        return chatWidget;
    }
    
    QWidget* createRightSidebar() {
        QWidget *sidebar = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(sidebar);
        
        QTabWidget *settingsTab = new QTabWidget();
        
        // Local Model Settings
        QWidget *localSettings = new QWidget();
        QVBoxLayout *localLayout = new QVBoxLayout(localSettings);
        
        QLabel *samplerLabel = new QLabel("Sampling Method:");
        QComboBox *samplerCombo = new QComboBox();
        samplerCombo->addItems({"Temperature", "Top-P", "Top-K"});
        
        QLabel *tempLabel = new QLabel("Temperature:");
        QSpinBox *tempSpinner = new QSpinBox();
        tempSpinner->setRange(1, 200);
        tempSpinner->setValue(70);
        
        QLabel *contextLabel = new QLabel("Context Length:");
        QSpinBox *contextSpinner = new QSpinBox();
        contextSpinner->setRange(512, 8192);
        contextSpinner->setValue(2048);
        
        localLayout->addWidget(samplerLabel);
        localLayout->addWidget(samplerCombo);
        localLayout->addWidget(tempLabel);
        localLayout->addWidget(tempSpinner);
        localLayout->addWidget(contextLabel);
        localLayout->addWidget(contextSpinner);
        localLayout->addStretch();
        
        // API Settings
        QWidget *apiSettings = new QWidget();
        QVBoxLayout *apiLayout = new QVBoxLayout(apiSettings);
        
        QLabel *apiKeyLabel = new QLabel("API Key:");
        QTextEdit *apiKeyInput = new QTextEdit();
        apiKeyInput->setMaximumHeight(30);
        
        QLabel *tokenLimitLabel = new QLabel("Token Limit:");
        QSpinBox *tokenLimitSpinner = new QSpinBox();
        tokenLimitSpinner->setRange(100, 10000);
        tokenLimitSpinner->setValue(2000);
        
        apiLayout->addWidget(apiKeyLabel);
        apiLayout->addWidget(apiKeyInput);
        apiLayout->addWidget(tokenLimitLabel);
        apiLayout->addWidget(tokenLimitSpinner);
        apiLayout->addStretch();
        
        settingsTab->addTab(localSettings, "Local Model");
        settingsTab->addTab(apiSettings, "API Settings");
        
        layout->addWidget(settingsTab);
        
        return sidebar;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LLMInterface window;
    window.show();
    return app.exec();
}