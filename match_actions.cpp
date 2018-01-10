#include "pass_runner.h"
#include <QDir>
#include <KLocalizedString>

using namespace std;

Plasma::QueryMatch pass_runner::helloWorld() {
	Plasma::QueryMatch match(this);
	
	match.setType(Plasma::QueryMatch::Type::ExactMatch);
	match.setText(QLatin1String("Hello KRunner Pass!"));

	return match;
}

QList<Plasma::QueryMatch> pass_runner::helloPath()
{
	QList<Plasma::QueryMatch> matches;

	QDir root(m_path);
	QStringList dirs = root.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

	Plasma::QueryMatch count(this);
	count.setType(Plasma::QueryMatch::Type::ExactMatch);
	count.setText(tr("%1").arg(dirs.count()));
	matches.append(count);
	
	foreach (QString dir, dirs)
	{
		Plasma::QueryMatch match(this);
		match.setType(Plasma::QueryMatch::Type::InformationalMatch);
		match.setText(dir);
		matches.append(match);
	}
	return matches;
}
