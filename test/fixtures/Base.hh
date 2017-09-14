<?hh //partial

namespace HHPack\Package\Test\Fixtures;

class Base {

  public function __construct(private $name = '') {}

  public function getName(): string {
    return $this->name;
  }

}
