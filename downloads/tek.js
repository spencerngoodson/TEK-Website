const pageIds = ['home', 'about', 'activities', 'rush'];
const pages = Object.fromEntries(pageIds.map(id => [id, document.getElementById(id)]));
const navLinks = Array.from(document.querySelectorAll('[data-page-link]'));
const menuBtn = document.getElementById('menuBtn');
const navLinksBox = document.getElementById('navLinks');

function setActivePage(id) {
  const target = pages[id] || pages.home;
  pageIds.forEach(pid => pages[pid].classList.toggle('active', pid === target.id));
  navLinks.forEach(link => link.classList.toggle('active', link.dataset.pageLink === target.id));
  window.scrollTo({ top: 0, behavior: 'smooth' });
  history.replaceState(null, '', `#${target.id}`);
  navLinksBox.classList.remove('open');
  menuBtn.setAttribute('aria-expanded', 'false');
}

function initFromHash() {
  const hash = (location.hash || '#home').replace('#', '');
  setActivePage(pageIds.includes(hash) ? hash : 'home');
}

navLinks.forEach(link => {
  link.addEventListener('click', (e) => {
    const id = link.dataset.pageLink;
    if (pageIds.includes(id)) {
      e.preventDefault();
      setActivePage(id);
    }
  });
});

menuBtn.addEventListener('click', () => {
  const isOpen = navLinksBox.classList.toggle('open');
  menuBtn.setAttribute('aria-expanded', String(isOpen));
});

window.addEventListener('hashchange', initFromHash);
initFromHash();
