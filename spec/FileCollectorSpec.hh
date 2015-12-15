<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\FileCollector;

describe(FileCollector::class, function () {
  beforeEach(function () {
    $this->collector = new FileCollector(__DIR__ . '/fixtures');
  });
  describe('collect()', function () {
    it('returns files', function () {
      $files = $this->collector->collect();
      expect($files->toImmVector()->count())->toBe(2);
    });
  });
});
