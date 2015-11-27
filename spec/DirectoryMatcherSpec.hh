<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\DirectoryMatcher;

describe(DirectoryMatcher::class, function () {
  beforeEach(function () {
    $this->matcher = new DirectoryMatcher();
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
