#include "pass_runner.h"
#include <QDir>
#include <KLocalizedString>

using namespace std;

K_EXPORT_PLASMA_RUNNER(pass_runner, pass_runner)

pass_runner::pass_runner(QObject *parent, const QVariantList &args)
	: Plasma::AbstractRunner(parent, args)
{
	// General runner configuration
	setObjectName(QLatin1String("Password Store"));
	m_triggerWord = QLatin1String("kpass ");

	setSpeed(AbstractRunner::NormalSpeed);
	setPriority(HighestPriority);
	setIgnoredTypes(Plasma::RunnerContext::NetworkLocation |
					Plasma::RunnerContext::Help |
					Plasma::RunnerContext::FileSystem);

	setDefaultSyntax(
		Plasma::RunnerSyntax(
			QString::fromLatin1("kpass :q:"),
			i18n("Looks for a password in Password Store described by :q: and, if present, displays it. Then pressing ENTER copies the password to the clipboard.")
		)
	);
}

pass_runner::~pass_runner()
{
}

void pass_runner::init()
{
	reloadConfiguration();
}

void pass_runner::reloadConfiguration()
{
	KConfigGroup c = config();

	QDir path(QDir::homePath() + QDir::separator() + QString::fromLatin1(".password-store"));
	m_path = c.readPathEntry("store-path", path.absolutePath());
	QFileInfo pathInfo(m_path);
	if (!pathInfo.isDir()) {
		m_path = path.absolutePath();
	}
}

void pass_runner::match(Plasma::RunnerContext &context)
{
	const QString term = context.query();
	if (!context.isValid() || m_triggerWord.isEmpty() || !term.startsWith(m_triggerWord)) return;

	context.addMatch(helloWorld());
	context.addMatches(helloPath());
}

void pass_runner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
	Q_UNUSED(context)
	Q_UNUSED(match)
}

#include "pass_runner.moc"
