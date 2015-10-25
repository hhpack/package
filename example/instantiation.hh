<?hh // partial

namespace hhpack\package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\package\Package;

$classes = Package::fromOptions(shape(
    'namespace' => 'hhpack\\package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
))->classes()->toImmVector();

foreach ($classes as $class) {
    $instance = $class->instantiate();
    var_dump($instance);
}
