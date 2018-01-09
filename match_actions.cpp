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
