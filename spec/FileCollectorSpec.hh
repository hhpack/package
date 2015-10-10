<?hh //partial

namespace package\spec;

use package\FileCollector;

describe(FileCollector::class, function () {
  beforeEach(function () {
    $this->collector = new FileCollector();
  });
  describe('collectFrom()', function () {
    it('returns files', function () {
      $files = $this->collector->collectFrom(__DIR__ . '/fixtures');
      expect($files->toImmVector()->count())->toBe(2);
    });
  });
});
