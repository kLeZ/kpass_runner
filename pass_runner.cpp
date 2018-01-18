#include "pass_runner.h"

static const QString s_copyToClipboardId = QStringLiteral("copyToClipboard");

K_EXPORT_PLASMA_RUNNER(pass_runner, KPassRunner)

KPassRunner::KPassRunner(QObject *parent, const QVariantList &args)
	: Plasma::AbstractRunner(parent, args)
{
	// General runner configuration
	setObjectName(QLatin1String("Password Store"));
	m_triggerWord = QLatin1String("kpass ");

	setSpeed(AbstractRunner::NormalSpeed);
	setPriority(HighestPriority);
	setIgnoredTypes(Plasma::RunnerContext::NetworkLocation |
					Plasma::RunnerContext::FileSystem);

	QString desc = i18n("Looks for a password in Password Store described by :q: and, if present, displays it. Then pressing ENTER copies the password to the clipboard.");
	addSyntax(Plasma::RunnerSyntax(QStringLiteral(":q:").prepend(m_triggerWord), desc));
	addAction(s_copyToClipboardId, QIcon::fromTheme(QStringLiteral("edit-copy")), i18n("Copy to Clipboard"));
}

KPassRunner::~KPassRunner()
{
}

void KPassRunner::init()
{
	reloadConfiguration();
}

void KPassRunner::reloadConfiguration()
{
	KConfigGroup c = config();

	QDir path(QDir::homePath() + QDir::separator() + QString::fromLatin1(".password-store"));
	m_path = c.readPathEntry("store-path", path.absolutePath());
	QFileInfo pathInfo(m_path);
	if (!pathInfo.isDir())
	{
		m_path = path.absolutePath();
	}
}

void KPassRunner::match(Plasma::RunnerContext &context)
{
	const QString term = context.query();

	if (!context.isValid() || m_triggerWord.isEmpty() || !term.startsWith(m_triggerWord)) return;

	QString key = term.mid(m_triggerWord.size());
// 	context.addMatch(helloWorld());
	context.addMatches(findPaths(key));
}

void KPassRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
	Q_UNUSED(context);
	if (match.selectedAction() == action(s_copyToClipboardId))
	{
		QGuiApplication::clipboard()->setText("This is actually an InformationalMatch");
	}
}

QList<QAction *> KPassRunner::actionsForMatch(const Plasma::QueryMatch &match)
{
	Q_UNUSED(match);
	return {action(s_copyToClipboardId)};
}

QMimeData * KPassRunner::mimeDataForMatch(const Plasma::QueryMatch &match)
{
	QMimeData *result = new QMimeData();
	result->setText(match.text());
	return result;
}

#include "pass_runner.moc"
