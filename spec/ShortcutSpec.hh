<?hh //partial

namespace hhpack\package\spec;

use hhpack\package as package;
use hhpack\package\SourceFile;
use hhpack\package\spec\mock\ResourceMock;

describe('package', function () {
  describe('package\startsWith', function () {
    beforeEach(function () {
      $this->item = new ResourceMock('foobar');
    });
    context('when matched', function () {
      it('returns true', function () {
        $matcher = package\startsWith('foo');
        expect($matcher($this->item))->toBeTrue();
      });
    });
  });
  describe('package\endsWith', function () {
    beforeEach(function () {
      $this->item = new ResourceMock('foobar');
    });
    context('when matched', function (){
      it('returns true', function () {
        $matcher = package\endsWith('bar');
        expect($matcher($this->item))->toBeTrue();
      });
    });
  });
});
