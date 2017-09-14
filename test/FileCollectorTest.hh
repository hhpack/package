<?hh //strict

namespace HHPack\Package\Test;

use HHPack\Package\FileCollector;
use HackPack\HackUnit\Contract\Assert;

final class FileCollectorTest {
  <<Test>>
  public function collectFiles(Assert $assert): void {
    $collector = new FileCollector(__DIR__.'/fixtures');
    $files = $collector->collect();

    $assert->int($files->toImmVector()->count())->eq(2);
  }
}
