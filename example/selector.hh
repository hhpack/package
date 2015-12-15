<?hh // partial

namespace hhpack\package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\package;
use hhpack\package\selector;

$pkg = package\package(shape(
    'namespace' => 'hhpack\\package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
));

$classes = $pkg->classes(selector\startsWith('Exa'))
    ->toImmVector()
    ->items();

foreach ($classes as $class) {
    var_dump($class->getName());
}
