/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Package;

final class FileCollector
  implements Collector<SourceFile, ResourceStream<SourceFile>> {

  public function __construct(private string $directory) {}

  public function collect(
    (function(SourceFile): bool) $matcher = any(),
  ): ResourceStream<SourceFile> {
    $factory = () ==> {
      $dir = \realpath($this->directory);
      foreach ($this->findFiles($dir) as $collectedFile) {
        yield new SourceFile($collectedFile);
      }
    };

    return ResourceStream::fromItems($factory())->filter($matcher);
  }

  private function findFiles(string $dir): Iterator<string> {
    // GLOB_NOSORT = 4, GLOB_BRACE = 128
    foreach (\glob($dir.'/{*.hh,*.hack}', \GLOB_NOSORT | \GLOB_BRACE) as $file) {
      yield $file;
    }

    $directories = \glob($dir.'/*', \GLOB_ONLYDIR);

    foreach ($directories as $directory) {
      $files = $this->findFiles($directory);

      foreach ($files as $file) {
        yield $file;
      }
    }
  }

}
