namespace HHPack\Package\Test;

use HHPack\Package\FileCollector;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class FileCollectorTest extends HackTest {
  public function testCollectFiles(): void {
    $collector = new FileCollector(__DIR__.'/fixtures');
    $files = $collector->collect();

    expect($files->toImmVector()->count())->toBeSame(3);
  }
}
