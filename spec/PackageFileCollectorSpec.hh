<?hh //partial

namespace package\spec;

use package\PackageFileCollector;

describe(PackageFileCollector::class, function () {
  beforeEach(function () {
    $this->collector = new PackageFileCollector();
  });
  describe('collectFrom()', function () {
    it('returns files', function () {
      $items = Vector {};
      $files = $this->collector->collectFrom(__DIR__ . '/fixtures');

      foreach ($files as $file) {
        $items->add($file);
      }
      expect($items->count())->toBe(1);
    });
  });
});
