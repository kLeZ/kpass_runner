#include "pass_runner.h"

using namespace std;

K_EXPORT_PLASMA_RUNNER(pass_runner, pass_runner)

pass_runner::pass_runner(QObject *parent, const QVariantList &args)
	: Plasma::AbstractRunner(parent, args)
{
	// General runner configuration
	setObjectName(QLatin1String("Password Store"));
	m_triggerWord = QLatin1String("kpass");

	setSpeed(AbstractRunner::NormalSpeed);
	setPriority(HighestPriority);
	setHasRunOptions(true);

	setDefaultSyntax(
		Plasma::RunnerSyntax(
			QString::fromLatin1("kpass :q:"),
			"Looks for a password in Password Store described by :q: and, if present, displays it. Then pressing ENTER copies the password to the clipboard."
		)
	);
}

pass_runner::~pass_runner()
{
}


void pass_runner::match(Plasma::RunnerContext &context)
{
	if (!context.isValid()) return;
	const QString term = context.query();
	if (!m_triggerWord.isEmpty()) {
		if (!term.startsWith(m_triggerWord)) {
			return;
		}
	}

	Plasma::QueryMatch match(this);

	match.setType(Plasma::QueryMatch::Type::ExactMatch);
	match.setText(QLatin1String("Hello KPass!"));
	context.addMatch(match);
}

void pass_runner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
	Q_UNUSED(context)
	Q_UNUSED(match)
}

#include "pass_runner.moc"
