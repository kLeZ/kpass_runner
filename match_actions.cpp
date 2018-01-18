#include "pass_runner.h"

using namespace std;

Plasma::QueryMatch KPassRunner::helloWorld() {
	Plasma::QueryMatch match(this);
	
	match.setType(Plasma::QueryMatch::Type::InformationalMatch);
	match.setText(QLatin1String("kpass Hello KRunner Pass!"));

	return match;
}

QList<Plasma::QueryMatch> KPassRunner::findPaths(QString &term)
{
	QList<Plasma::QueryMatch> matches;

	QDir root(m_path);
	if (term.contains(QDir::separator())) {
		QStringList splitted = term.split(QDir::separator(), QString::SplitBehavior::SkipEmptyParts, Qt::CaseSensitivity::CaseInsensitive);
		QString last = splitted.takeLast();
		root.cd(last); //BUG: do not take in consideration multiple separators
	}
	QStringList dirs = root.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable);

	foreach (QString dir, dirs)
	{
		if (dir.compare(term, Qt::CaseSensitivity::CaseInsensitive) == 0) {
			Plasma::QueryMatch match(this);
			match.setType(Plasma::QueryMatch::Type::InformationalMatch);
			match.setText(dir);
			match.setData(dir.prepend(m_triggerWord).append('/'));
			matches.append(match);
		} else if (dir.startsWith(term, Qt::CaseSensitivity::CaseInsensitive)) {
			Plasma::QueryMatch match(this);
			match.setType(Plasma::QueryMatch::Type::InformationalMatch);
			match.setText(dir);
			match.setData(dir.prepend(m_triggerWord).append('/'));
			matches.append(match);
		}
	}
	return matches;
}
