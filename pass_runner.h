#ifndef PASS_RUNNER_H
#define PASS_RUNNER_H

#include <krunner/abstractrunner.h>
#include <QDir>
#include <KLocalizedString>
#include <QGuiApplication>
#include <QClipboard>
#include <QMimeData>

class KPassRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    KPassRunner(QObject *parent, const QVariantList &args);
    ~KPassRunner();

	void init() override;
	void reloadConfiguration() override;
	void match(Plasma::RunnerContext &context) override;

protected Q_SLOTS:
	void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;
	QList<QAction *> actionsForMatch(const Plasma::QueryMatch &match) override;
	QMimeData * mimeDataForMatch(const Plasma::QueryMatch &match) override;

private:
	Plasma::QueryMatch helloWorld();
	QList<Plasma::QueryMatch> findPaths(QString &term);

	QString m_triggerWord;
	QString m_path;
};

#endif
