<?hh // partial

namespace hhpack\package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\package\Package;
use hhpack\package\selector;

$pkg = Package::fromOptions(shape(
    'namespace' => 'hhpack\\package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
));

$classes = $pkg->classes(selector\startsWith('Exa'))
    ->toImmVector()
    ->items();

foreach ($classes as $class) {
    var_dump($class->getName());
}
