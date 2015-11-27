<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\HackSourceFileMathcer;

describe(HackSourceFileMathcer::class, function () {
  beforeEach(function () {
    $this->matcher = new HackSourceFileMathcer();
  });
  describe('matches()', function () {
    context('when matched', function () {
      it('returns true', function () {
        expect($this->matcher->matches('/path/to/source.hh'))->toBeTrue();
      });
    });
    context('when unmatched', function () {
      it('returns false', function () {
        expect($this->matcher->matches('/path/to/source'))->toBeFalse();
      });
    });
  });
});
