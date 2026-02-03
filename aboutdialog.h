#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTextBrowser>

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private:
    void setupUi();
    
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *versionLabel;
    QTextEdit *disclaimerTextEdit;
    QTextBrowser *copyrightTextEdit;
    QPushButton *closeButton;
};

#endif // ABOUTDIALOG_H
