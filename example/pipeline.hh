<?hh // partial

namespace hhpack\package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\package;
use hhpack\package\examples\classes\FileStatOutput;
use hhpack\package\examples\classes\FileStatStream;
use hhpack\package\examples\classes\FileStatTransformer;

$pkg = package\package(shape(
    'namespace' => 'hhpack\\package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
));

$pkg->sources()->pipeTo(new FileStatTransformer())->pipeTo(new FileStatOutput());
