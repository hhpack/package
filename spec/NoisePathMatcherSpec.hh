<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\NoisePathMatcher;

describe(NoisePathMatcher::class, function () {
  beforeEach(function () {
    $this->matcher = new NoisePathMatcher();
  });
  describe('matches()', function () {
    context('when matched', function () {
      it('returns true', function () {
        expect($this->matcher->matches('.'))->toBeTrue();
        expect($this->matcher->matches('..'))->toBeTrue();
      });
    });
  });
});
